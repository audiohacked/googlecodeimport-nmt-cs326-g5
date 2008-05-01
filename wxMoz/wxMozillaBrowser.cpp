/*
 * wxWindows Mozilla Browser Component
 * 
 * Developers:
 *  Jeremiah Cornelius McCarthy <jeremiah@whoop-ass.ca>
 *  Kevin Ollivier <kevino@tulane.edu>
 *  Dave Fancella <david.fancella@attbi.com>
 */

#include "wx/wxprec.h"

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#include "wx/dynlib.h"
#include "wx/filename.h"
#include "wx/control.h"
#include "wx/log.h"
#include "wx/dialog.h"
#include "wx/dc.h"
#include "wx/module.h"
#include "wxMozillaBrowser.h"
#include "wxMozillaBrowserChrome.h"
#include "wxMozillaSettings.h"

#include "nsIWidget.h"
#include "nsIWebNavigation.h"
#include "nsWidgetsCID.h"
#include "nsRect.h"
#include "mozilla-config.h"
//#include "nsISHistoryListener.h"
#include "nsString.h"
#include "nsCOMPtr.h"
#include "nsIEventQueueService.h"

#include "nsIComponentRegistrar.h"

#include "nsIInputStream.h"
#include "nsIAtom.h"
#include "nsIPref.h"
#include "nsISupports.h"
#include "nsIBaseWindow.h"
#include "nsIWebBrowser.h"
#include "nsIWebBrowserPersist.h"
#include "nsIWebBrowserChrome.h"
#include "nsIEmbeddingSiteWindow.h"
#include "nsEmbedAPI.h"
#include "nsIWindowCreator.h"
#include "nsIWindowWatcher.h"
#include "nsCWebBrowser.h"
#include "nsIWebProgressListener.h"
#include "nsIContextMenuListener2.h"
#include "nsIInterfaceRequestor.h"
#include "nsIWebBrowserSetup.h"
#include "nsIDocShellTreeItem.h"
#include "nsIWebBrowserChromeFocus.h"
#include "nsIInterfaceRequestor.h"
#include "nsIInterfaceRequestorUtils.h"
#include "nsReadableUtils.h"
#include "nsIWeakReference.h"
#include "nsIWeakReferenceUtils.h"
#include "nsWeakReference.h"
#include "wx/event.h"
#include "nsISelection.h"
#include "nsIURI.h"
#include "nsIClipboardCommands.h"
#include "nsIWebBrowserFind.h"
#include "nsIDOMWindow.h"

#include "nsIDOMEventListener.h"
#include "nsPIDOMWindow.h"
#include "nsIChromeEventHandler.h"
#include "nsIDOMWindowInternal.h"
#include "nsIDocShell.h"
#include "nsIDocument.h"
#include "nsIDOMDocument.h"
#include "nsIDocumentEncoder.h"
#include "nsIStringStream.h"
#include "nsIAppShell.h"
#include "nsIEditorSpellCheck.h"
#include "nsIURIContentListener.h"

#include "nsICookieManager.h"
#include "nsICookieService.h"
#include "nsNetUtil.h"

/**
 * @author David Teller <Yoric@users.sourceforge.net>
 * For zooming
 */
#include "nsIMarkupDocumentViewer.h"
#include "nsIContentViewer.h"

#ifdef __WXMAC__
#include <Carbon/Carbon.h>
#endif

#include "wxMozillaBrowserInterface.h"
#include "helpers.h"

#ifdef XPCOM_GLUE
#include "nsXPCOMGlue.h"
#endif

#ifdef __WXMAC__
#include "Carbon/Carbon.h"
#include "wx/mac/uma.h"
#endif
//#include "wx/app.h" //wxPostEvent
#include "nsIWeakReference.h" //for nsIProgressListener
//#include "winEmbedFileLocProvider.h"

#include "wxMozillaDialogs.h"
#define NS_PROMPTSERVICE_CID \
 {0xa2112d6a, 0x0e28, 0x421f, {0xb4, 0x6a, 0x25, 0xc0, 0xb3, 0x8, 0xcb, 0xd0}}
static NS_DEFINE_CID(kPromptServiceCID, NS_PROMPTSERVICE_CID);

static NS_DEFINE_IID(kWindowCID, NS_WINDOW_CID);
static NS_DEFINE_CID(kEventQueueServiceCID, NS_EVENTQUEUESERVICE_CID);
static NS_DEFINE_CID(kAppShellCID, NS_APPSHELL_CID);

static NS_DEFINE_CID(kCookieServiceCID, NS_COOKIESERVICE_CID);


#ifdef __WXGTK__
    #include <gtk/gtk.h>
    #include <gdk/gdk.h>
    static gint io_id = 0;
    static void handle_event_queue(gpointer data,  gint source, GdkInputCondition cond)
    {
        nsIEventQueue *eventQueue = (nsIEventQueue *)data;
	eventQueue->ProcessPendingEvents();
    }
#endif

IMPLEMENT_DYNAMIC_CLASS(wxMozillaBrowser, wxWindow)

BEGIN_EVENT_TABLE(wxMozillaBrowser, wxWindow)
	EVT_SIZE(wxMozillaBrowser::OnSize)
	EVT_ACTIVATE(wxMozillaBrowser::OnActivate)
    #ifdef __WXMAC__ //need to override wxMac event handlers for Mozilla
        EVT_PAINT(wxMozillaBrowser::OnPaint)
        EVT_MOVE(wxMozillaBrowser::OnMove)
        EVT_MOUSE_EVENTS(wxMozillaBrowser::OnMouseEvent)
        EVT_SET_FOCUS(wxMozillaBrowser::OnSetFocus)
        EVT_KILL_FOCUS(wxMozillaBrowser::OnKillFocus)        
    #endif
END_EVENT_TABLE()

const wxChar *wxMozillaBrowserNameStr = wxT("Mozilla");


int wxMozillaBrowser::gNumInstances = 0;  

static bool gEmbeddingInitialized = FALSE;
nsIAppShell *gAppShell = NULL;

wxString FindGRE(){
#ifdef __WXMSW__
	 wxChar* pGreLocation = NULL;
     //Get location of GRE
     HKEY hRegKey = NULL;
     DWORD dwLength = _MAX_PATH * sizeof(wxChar);
     long rc;
     wxChar keyValue[_MAX_PATH + 1];

     if (::RegOpenKeyEx(HKEY_LOCAL_MACHINE, TEXT("Software\\mozilla.org\\GRE\\wxMozilla"), 0, KEY_QUERY_VALUE, &hRegKey) == ERROR_SUCCESS) 
     {
         if ((rc = ::RegQueryValueEx(hRegKey, TEXT("GreHome"), NULL, NULL, (BYTE *)keyValue, &dwLength))==ERROR_SUCCESS)
         {
             pGreLocation = wxStrdup(keyValue);
             ::RegCloseKey(hRegKey);
		}
     }
	 return wxString(pGreLocation, wxConvFile);
#endif
}


/**
 * Creates a new instances of a Mozilla browser component class
 *
 * @param None.
 *
 * @return Class instance.
 */

wxMozillaBrowser::wxMozillaBrowser() : m_Mozilla(NULL)
{
}

wxMozillaBrowser::wxMozillaBrowser(wxWindow *parent, wxWindowID id, const wxPoint &pos, const wxSize &size, long style, const wxString &name)
{

    Create(parent, id, pos, size, style, name);
}
/**
 * Destroys the instance
 * 
 * @param none
 * @return Nothing
 */
wxMozillaBrowser::~wxMozillaBrowser()
{
    //remove mouse event listener
	nsIDOMEventListener *eventListener = NS_STATIC_CAST(nsIDOMEventListener *, NS_STATIC_CAST(nsIDOMKeyListener *, Chrome));

    m_Mozilla->mEventReceiver->RemoveEventListenerByIID(eventListener,
					     NS_GET_IID(nsIDOMKeyListener));

#ifndef __WXMAC__
	m_Mozilla->mEventReceiver->RemoveEventListenerByIID(eventListener,
					     NS_GET_IID(nsIDOMMouseListener));
#endif

	//having an open selection can freeze Mozilla.
	if (m_Mozilla->mWebNav)
		m_Mozilla->mWebNav = nsnull;
	if (m_Mozilla->mBaseWindow)
	{
		m_Mozilla->mBaseWindow->Destroy();
		m_Mozilla->mBaseWindow = nsnull;
	}
	if (m_Mozilla->mWebBrowser)
		m_Mozilla->mWebBrowser = nsnull;

	if (m_Mozilla->mCommandManager)
		m_Mozilla->mCommandManager = nsnull;

	if (m_Mozilla->mEditingSession)
		m_Mozilla->mEditingSession = nsnull;

    if (m_Mozilla->mEventReceiver)
        m_Mozilla->mEventReceiver = nsnull;

    if (m_Mozilla->mSelectedElement)
        m_Mozilla->mSelectedElement = nsnull;

	if (Chrome)
	{
		Chrome->Release();
		Chrome = nsnull;
	}
#ifdef __WXMAC__
    if ( m_Mozilla->mEventSink )
    {
        m_Mozilla->mEventSink = nsnull;
    }
#endif

	delete m_Mozilla;
	wxMozillaBrowser::gNumInstances--;
}

void wxMozillaShutdown(){
    if (gEmbeddingInitialized)
    {
        wxMozillaSettings::CleanUp();

        if (gAppShell) {
            gAppShell->Spindown();
            NS_RELEASE(gAppShell);
            gAppShell = NULL;
        }

        
#ifdef XPCOM_GLUE
        NS_ShutdownXPCOM(nsnull);
        XPCOMGlueShutdown();
#else
        #if WXMOZ_FIREFOX_VERSION >= 15 || WXMOZ_SEAMONKEY_VERSION >= 10 || WXMOZ_XUL_VERSION >= 18
        NS_ShutdownXPCOM(nsnull);
        #else
		NS_TermEmbedding();
        #endif
#endif
        #ifdef __WXGTK__
             gdk_input_remove(io_id);
		#endif
    }
}

bool wxMozillaBrowser::IsEmbeddingInitialized()
{
    return gEmbeddingInitialized;
}

bool wxMozillaBrowser::EnsureEmbedding()
{
    if (!gEmbeddingInitialized)
    {
	    nsresult rv;
        nsCOMPtr<nsILocalFile> greDir;
        greDir = nsnull;
        wxString greLocation(wxMozillaSettings::GetMozillaPath());

        if (greLocation.empty())
#ifdef __UNIX__
            greLocation = wxString(MOZILLA_HOME, wxConvFile);
#elif defined(__WXMSW__)
            greLocation = FindGRE();
#endif    

        wxString curDir = wxGetCwd();
        if (!greLocation.empty())
        {
            wxSetWorkingDirectory(greLocation);
            
            //if greDir is nsnull, then look for libraries in current directory
            nsresult rv;

#ifdef XPCOM_GLUE
        XPCOMGlueStartup((greLocation+_T("xpcom.dll")).mb_str(wxConvFile));
#endif

            rv = NS_NewNativeLocalFile(nsDependentCString(greLocation.mb_str(wxConvFile)), TRUE, getter_AddRefs(greDir));
            if (NS_FAILED(rv))
            {
                wxLogError(wxT("Did not create local file!"));
                return FALSE;
            }
        }
#ifdef XPCOM_GLUE
        XPCOMGlueStartup((greLocation+_T("xpcom.dll")).mb_str(wxConvFile));
        NS_InitXPCOM2(nsnull, greDir, nsnull); 
#else
        #if WXMOZ_FIREFOX_VERSION >= 15 || WXMOZ_SEAMONKEY_VERSION >= 10 || WXMOZ_XUL_VERSION >= 18
        rv = NS_InitXPCOM3(nsnull, greDir, nsnull, nsnull, nsnull);
        #else
        rv = NS_InitEmbedding(greDir, nsnull);
        #endif
        if (NS_FAILED(rv))
        {
            wxLogError(wxT("InitEmbedding Failed!"));
            return FALSE;
        }
#endif //XPCOM_GLUE
        
        // Initialize app shell -- otherwise GTK+2 port segfaults and other
        // things may not work correctly either
        nsCOMPtr<nsIAppShell> appShell;
        appShell = do_CreateInstance(kAppShellCID);
        if (!appShell) {
            wxLogError(wxT("Failed to create appshell!"));
            return FALSE;
        }
        gAppShell = appShell.get();
        NS_ADDREF(gAppShell);
        gAppShell->Create(0, nsnull);
        gAppShell->Spinup();
        

        gEmbeddingInitialized = TRUE;

        wxSetWorkingDirectory(curDir);

        // If profile path was set before initializing embedding, set it now: 
        wxString profilePath = wxMozillaSettings::GetProfilePath();
        if (!profilePath.empty())
            wxMozillaSettings::SetProfilePath(profilePath);
    }
    return true;
}


/**
 * Create an embedded mozilla component
 *
 * @param parent
 * 	Parent window
 * @param id
 * 	Id of window
 * @param pos
 * 	Position of window
 * @param size
 * 	Size of window
 * @param style
 * 	Style of window
 * @param name
 * 	Name of window
 * @return
 * 	True on sucess, False on failure
 */

bool wxMozillaBrowser::Create(wxWindow *parent, wxWindowID id, const wxPoint &pos, const wxSize &size, long style, const wxString &name)
{
	nsresult rv;
	
	m_needParent = TRUE;
	m_acceptsFocus = TRUE;
	m_isEditable = FALSE;
	m_isBusy = FALSE;

    m_Mozilla = new wxMozillaBrowserInterface;

        //initialize the base wxWindow...
    #ifdef __WXGTK__
        //for some reason, I get initialization errors if I call wxWindow::Create
        //even if I call gtk_widget_realize afterwards
        PreCreation(parent, pos, size);
	CreateBase(parent, id, pos, size, style, wxDefaultValidator, name);
	m_widget = gtk_event_box_new();
	m_parent->DoAddChild(this);
	PostCreation();

	gtk_widget_realize(GTK_WIDGET(m_parent->m_widget));
    gtk_widget_realize(GTK_WIDGET(m_widget));
	gtk_widget_show(GTK_WIDGET(m_widget));
	GTK_WIDGET_SET_FLAGS(m_widget, GTK_CAN_FOCUS);
    #else //this works on Windows and Mac
	wxWindow::Create(parent, id, pos, size, style, name);
    #endif
	/*
	 * MOZILLA
	 */
    
 
    if (!EnsureEmbedding())
        return FALSE;

	nsCOMPtr<nsIComponentRegistrar> compReg;
	nsresult rv2 = NS_GetComponentRegistrar(getter_AddRefs(compReg));
	NS_ENSURE_SUCCESS(rv2, rv2);


	nsCOMPtr <nsIEventQueueService> eventQService = do_GetService(kEventQueueServiceCID);
	if(!eventQService)
	{
		wxLogError(wxT("Failed to create EventQueueService!\n"));
		return FALSE;
	}
	
	eventQService->GetThreadEventQueue(NS_CURRENT_THREAD, getter_AddRefs(m_Mozilla->eventQueue));
	if(!m_Mozilla->eventQueue)
	{
		wxLogError(wxT("Failed to create EventQueue!\n"));
        return FALSE;
	}
#if __WXGTK__
	io_id = gdk_input_add(m_Mozilla->eventQueue->GetEventQueueSelectFD(), GDK_INPUT_READ, handle_event_queue, m_Mozilla->eventQueue);
#endif

	nsCOMPtr<nsIFactory> promptFactory;
    rv = NS_NewPromptServiceFactory(getter_AddRefs(promptFactory));
    if (NS_FAILED(rv)) return FALSE;
	//use our own (native) prompts instead of the Mozilla XUL default ones
	rv = compReg->RegisterFactory(kPromptServiceCID,
                                           "Prompt Service",
                                           "@mozilla.org/embedcomp/prompt-service;1",
                                           promptFactory /*,
                                           PR_TRUE*/); // replace existing
	if (NS_FAILED(rv)) {
		return FALSE;
	}

        //contains implementations of Mozilla interfaces
	Chrome = new wxMozillaBrowserChrome(this);
	if(!Chrome)
	{
		wxLogError(wxT("Failed to create chrome!\n"));
		return FALSE;
	}
	Chrome->AddRef();

	//create the web browser
	m_Mozilla->mWebBrowser = do_CreateInstance(NS_WEBBROWSER_CONTRACTID, &rv);
	if(NS_FAILED(rv))
	{
		wxLogError(wxT("Failed to create web browser. Exiting...\n"));
		return FALSE;
	}

	//tell it where to send events
    m_Mozilla->mWebBrowser->SetContainerWindow(NS_STATIC_CAST(nsIWebBrowserChrome *, Chrome));
	m_Mozilla->mWebBrowser->SetParentURIContentListener(NS_STATIC_CAST(nsIURIContentListener *, Chrome));

	//set the type (contentWrapper vs chromeWrapper)
	nsCOMPtr<nsIDocShellTreeItem> dsti = do_QueryInterface(m_Mozilla->mWebBrowser);
	dsti->SetItemType(nsIDocShellTreeItem::typeContentWrapper);

        //this is what we will use to bind Mozilla to the wxWindow control
	m_Mozilla->mBaseWindow = do_QueryInterface(m_Mozilla->mWebBrowser);
	int posx, posy;
	this->GetPosition(&posx, &posy);

	int sizex, sizey;
	this->GetSize(&sizex, &sizey);
    
    
//pass a handle to the native window to Mozilla
#ifdef __WXMSW__
	rv = m_Mozilla->mBaseWindow->InitWindow(nsNativeWidget(this->GetHWND()), nsnull, 0, 0, sizex, sizey);
#elif defined(__WXGTK__) 
        rv = m_Mozilla->mBaseWindow->InitWindow(nsNativeWidget(m_widget), nsnull, 0, 0, sizex, sizey);
#elif defined(__WXMAC__) 
        GetParent()->MacWindowToRootWindow( & posx , & posy ) ;
        rv = m_Mozilla->mBaseWindow->InitWindow(nsNativeWidget(this->MacGetTopLevelWindowRef()), nsnull, posx, posy, sizex, sizey);
        //needed to start event handling on Mac
        m_Mozilla->mEventSink = do_GetInterface(m_Mozilla->mWebBrowser);
#endif 
    
	if(NS_FAILED(rv)){
		wxLogError(wxT("Couldn't initialize base window. Exiting...\n"));
		return FALSE;
     }
                
	rv = m_Mozilla->mBaseWindow->Create();
    if(NS_FAILED(rv)){
		wxLogError(wxT("Couldn't create base window. Exiting...\n"));
		return FALSE;
     }           

    rv = m_Mozilla->mBaseWindow->SetVisibility(PR_TRUE);

    //To get/update status
    nsWeakPtr weakling(dont_AddRef(NS_GetWeakReference(NS_STATIC_CAST(nsIWebProgressListener*, 
			Chrome))));
    (void)m_Mozilla->mWebBrowser->AddWebBrowserListener(weakling, NS_GET_IID(nsIWebProgressListener));

    
	nsCOMPtr<nsIDOMWindow> domWindow;
	m_Mozilla->mWebBrowser->GetContentDOMWindow(getter_AddRefs(domWindow));
	if (!domWindow)
	{
		wxLogError(wxT("Fatal Error: Cannot get DOM Window for browser.\n"));
		return FALSE;
	}

    	//This code lets us handle mouse events generated by Mozilla
	nsCOMPtr<nsPIDOMWindow> domWindowPrivate = do_QueryInterface(domWindow);
  	// and the root window for that DOM window
	nsCOMPtr<nsIDOMWindowInternal> rootWindow;
#ifdef MOZILLA_VERSION_U
	rootWindow = domWindowPrivate->GetPrivateRoot();
#else
	domWindowPrivate->GetPrivateRoot(getter_AddRefs(rootWindow));
#endif
  
	nsCOMPtr<nsPIDOMWindow> piWin(do_QueryInterface(rootWindow));

	if (!piWin)
		return FALSE;

	nsCOMPtr<nsIChromeEventHandler> chromeHandler;
#ifdef MOZILLA_VERSION_U 
	chromeHandler =  piWin->GetChromeEventHandler();
#else
	piWin->GetChromeEventHandler(getter_AddRefs(chromeHandler));
#endif


	m_Mozilla->mEventReceiver = do_QueryInterface(chromeHandler);

	nsIDOMEventListener *eventListener = NS_STATIC_CAST(nsIDOMEventListener *, NS_STATIC_CAST(nsIDOMKeyListener *, Chrome));

	m_Mozilla->mEventReceiver->AddEventListenerByIID(eventListener,
					     NS_GET_IID(nsIDOMKeyListener));

#ifndef __WXMAC__
    //This screws up Mouse up events in Mac
    m_Mozilla->mEventReceiver->AddEventListenerByIID(eventListener,
					     NS_GET_IID(nsIDOMMouseListener));
#endif
    //This code lets us handle pop-up windows 
	nsCOMPtr<nsIWindowCreator> windowCreator(NS_STATIC_CAST(nsIWindowCreator *, Chrome));
   if (windowCreator) {
     nsCOMPtr<nsIWindowWatcher> wwatch(do_GetService(NS_WINDOWWATCHER_CONTRACTID));
     if (wwatch) 
		 wwatch->SetWindowCreator(windowCreator);
	}

    //we need this for loading/navigating pages
    m_Mozilla->mWebNav = do_QueryInterface(m_Mozilla->mWebBrowser);
    nsCOMPtr<nsIWebBrowserFocus> browserAsFocus = do_QueryInterface(m_Mozilla->mWebBrowser);
	//it seems the initial focus event doesn't happen??
    browserAsFocus->Activate();

    nsCOMPtr<nsIWebBrowserSetup> mySetup = do_QueryInterface(m_Mozilla->mWebBrowser);
	mySetup->SetProperty(nsIWebBrowserSetup::SETUP_ALLOW_PLUGINS, PR_TRUE);
	wxMozillaBrowser::gNumInstances++;

    return TRUE;
}

void wxMozillaBrowser::OnIdle(wxIdleEvent &WXUNUSED(event) )
{
	if(m_Mozilla->eventQueue){
		m_Mozilla->eventQueue->ProcessPendingEvents();
	}
#ifdef __WXMAC__
            ::SetOrigin(0, 0);
#endif
}

wxString wxMozillaBrowser::GetStatus()
{
	return m_status;
}
    

#ifdef __WXGTK__
void wxMozillaBrowser::SetFocus()
{
    // NB: we intentionally don't call wxWindow::SetFocus() here -- if we
    //     did, focus setting wouldn't work (don't know why)
    
    m_Mozilla->mBaseWindow->SetFocus();
    nsCOMPtr<nsIWebBrowserFocus> browserAsFocus = do_QueryInterface(m_Mozilla->mWebBrowser);
    if (browserAsFocus)
        browserAsFocus->Activate();
}
#endif

/**
 * Handles sizing of the component
 *
 * @param pEvent
 * 	Pointer to the size event class
 *
 * @return
 * 	Nothing
 */
void wxMozillaBrowser::OnSize(wxSizeEvent &WXUNUSED(event))
{
#ifdef __WXMAC__
    wxPaintDC dc(this);
    wxMacPortSetter helper(&dc);
    wxMacWindowClipper clipper(this);

	wxRect newRect;
	wxSize newSize;
    this->GetSize (&newSize.x, &newSize.y);
    newSize.x -= this->MacGetLeftBorderSize () * 2;
    newSize.y -= this->MacGetTopBorderSize () * 2;
	newRect.SetWidth(newSize.x);
	newRect.SetHeight(newSize.y);
    this->MacClientToRootWindow (&newRect.x, &newRect.y);
#else
	wxRect newRect = this->GetClientRect();
#endif
	if (m_Mozilla->mBaseWindow)
		m_Mozilla->mBaseWindow->SetPositionAndSize(newRect.GetLeft(), newRect.GetTop(),
                                    newRect.GetWidth(),
                                    newRect.GetHeight(), PR_FALSE);
#ifdef __WXMAC__                                    
    ::SetOrigin(0, 0);
#endif
}

void wxMozillaBrowser::OnActivate(wxActivateEvent &pEvent){
    nsCOMPtr<nsIWebBrowserFocus> browserAsFocus = do_QueryInterface(m_Mozilla->mWebBrowser);
    if (browserAsFocus)
    {
		if (pEvent.GetActive()){
			browserAsFocus->Activate();
		}
		else{
			browserAsFocus->Deactivate();
		}
    }
#ifdef __WXMAC__
    ::SetOrigin(0, 0);
#endif
    pEvent.Skip();
}

#ifdef __WXMAC__
void wxMozillaBrowser::MacVisibilityChanged( ) 
{
    bool show = IsShown();
    PRBool showme = PR_FALSE;
    if (show)
        showme = PR_TRUE;
    m_Mozilla->mBaseWindow->SetVisibility(showme);
    ::SetOrigin(0, 0);
}

void wxMozillaBrowser::MacRedraw(WXHRGN updatergnr , long time, bool erase)
{
    EventRecord osEvent;
    osEvent.what = updateEvt;
    PRBool handled = PR_FALSE;
    if (m_Mozilla->mEventSink)
        m_Mozilla->mEventSink->DispatchEvent(&osEvent, &handled);
    ::SetOrigin(0, 0);
}

void wxMozillaBrowser::MacSuperChangedPosition() 
{
    wxWindow::MacSuperChangedPosition() ;
    wxPaintDC dc(this);
    wxMacPortSetter helper(&dc);
    wxMacWindowClipper clipper(this);

    int x, y, width, height;
    x = y = width = height = 0;
    this->GetSize (&width, &height);
    width -= this->MacGetLeftBorderSize () * 2;
    height -= this->MacGetTopBorderSize () * 2;
    this->MacClientToRootWindow (&x, &y);
    wxRect rect (x, y, width, height);
    m_Mozilla->mBaseWindow->SetPositionAndSize(rect.GetLeft(), rect.GetTop(),
                                    rect.GetWidth(),
                                    rect.GetHeight(), PR_TRUE);
        ::SetOrigin(0, 0);
}


void wxMozillaBrowser::MacEnabledStateChanged( ) 
{
    bool enabled = IsEnabled();
    PRBool isEnabled = PR_FALSE;
    if (enabled)
        isEnabled = PR_TRUE;
    m_Mozilla->mBaseWindow->SetEnabled(isEnabled);
    ::SetOrigin(0, 0);
}


void wxMozillaBrowser::OnSetFocus(wxFocusEvent &pEvent){
    printf("Setting focus...\n");
    EventRecord osEvent;
    osEvent.what = activateEvt;
    osEvent.modifiers = activeFlag;
    PRBool handled = PR_FALSE;
    if (m_Mozilla->mEventSink)
        m_Mozilla->mEventSink->DispatchEvent(&osEvent, &handled);

    m_Mozilla->mBaseWindow->SetFocus();
    nsCOMPtr<nsIWebBrowserFocus> browserAsFocus = do_QueryInterface(m_Mozilla->mWebBrowser);
    if (browserAsFocus)
        browserAsFocus->Activate();
    ::SetOrigin(0, 0);
    pEvent.Skip();
}

void wxMozillaBrowser::OnKillFocus(wxFocusEvent &pEvent){
    EventRecord osEvent;
    osEvent.what = activateEvt;
    osEvent.modifiers = 0;
    PRBool handled = PR_FALSE;
    if (m_Mozilla->mEventSink)
        m_Mozilla->mEventSink->DispatchEvent(&osEvent, &handled);
    nsCOMPtr<nsIWebBrowserFocus> browserAsFocus = do_QueryInterface(m_Mozilla->mWebBrowser);
    if (browserAsFocus)
        browserAsFocus->Deactivate();
    ::SetOrigin(0, 0);
    pEvent.Skip();
}

void wxMozillaBrowser::OnPaint(wxPaintEvent &pEvent)
{
    EventRecord osEvent;
    osEvent.what = updateEvt;
    PRBool handled = PR_FALSE;
    if (m_Mozilla->mEventSink)
        m_Mozilla->mEventSink->DispatchEvent(&osEvent, &handled);
    ::SetOrigin(0, 0);
}

void wxMozillaBrowser::OnMouseEvent(wxMouseEvent &pEvent)
{
    Rect clientrect = { GetPosition().x, GetPosition().y, GetPosition().x + GetSize().x, GetPosition().y + GetSize().y };
    
    EventRecord osEvent;
    ConvertEventRefToEventRecord((OpaqueEventRef*)wxTheApp->MacGetCurrentEvent(), &osEvent);
    PRBool handled = PR_FALSE;
    if (m_Mozilla->mEventSink)
        m_Mozilla->mEventSink->DispatchEvent(&osEvent, &handled);
    ::SetOrigin(0, 0);
    pEvent.Skip();
}

void wxMozillaBrowser::OnMove(wxMoveEvent &pEvent)
{
    wxPaintDC dc(this);
    wxMacPortSetter helper(&dc);
    wxMacWindowClipper clipper(this);

	wxRect newRect;
	wxSize newSize;
    this->GetSize (&newSize.x, &newSize.y);
    newSize.x -= this->MacGetLeftBorderSize () * 2;
    newSize.y -= this->MacGetTopBorderSize () * 2;
	newRect.SetWidth(newSize.x);
	newRect.SetHeight(newSize.y);
    this->MacClientToRootWindow (&newRect.x, &newRect.y);
    if (m_Mozilla->mBaseWindow)
            m_Mozilla->mBaseWindow->SetPositionAndSize(newRect.GetLeft(), newRect.GetTop(),
                                newRect.GetWidth(),
                                newRect.GetHeight(), PR_FALSE);
                                    
        ::SetOrigin(0, 0);
}
#endif

void wxMozillaBrowser::OnStatusChange()
{
#ifdef __WXMAC__
    ::SetOrigin(0, 0);
#endif
	wxMozillaStatusChangedEvent thisEvent = wxMozillaStatusChangedEvent(this);
	PRBool myresult = PR_FALSE;
	thisEvent.SetBusy(this->IsBusy());
	thisEvent.SetStatusText(this->m_status);
	GetEventHandler()->ProcessEvent(thisEvent);
}

void wxMozillaBrowser::OnLocationChange()
{
#ifdef __WXMAC__
    ::SetOrigin(0, 0);
#endif
	wxMozillaLinkChangedEvent thisEvent = wxMozillaLinkChangedEvent(this);
	thisEvent.SetCanGoBack(this->CanGoBack());
	thisEvent.SetCanGoForward(this->CanGoForward());
	thisEvent.SetNewURL(this->GetURL());
	GetEventHandler()->ProcessEvent(thisEvent);
}

bool wxMozillaBrowser::IsBusy()
{
	return m_isBusy;
}
/**
 * Opens a URL address
 *
 * @param location
 * 	The URL to open
 *
 * @return
 * 	True if sucessful, otherwise false
 */
bool wxMozillaBrowser::LoadURL(const wxString &location)
{
	if (m_Mozilla->mWebNav){
        nsresult rv;
        nsString mCurrentURI = wxString_to_nsString(location, wxConvISO8859_1);
		rv = m_Mozilla->mWebNav->LoadURI(mCurrentURI.get(), nsIWebNavigation::LOAD_FLAGS_NONE, NULL, NULL, NULL);
		if(NS_FAILED(rv)){
            wxLogError(_("Couldn't load URL: '%s'."), location.c_str());
			return FALSE;
        }
	}
	return TRUE;
}

/**
 * Returns the current URL address
 *
 * @return
 * 	Nothing
 */
wxString wxMozillaBrowser::GetURL()
{
	nsCAutoString aString;
	nsCOMPtr<nsIURI> currentURI;

	if (m_Mozilla->mWebNav){
		m_Mozilla->mWebNav->GetCurrentURI(getter_AddRefs(currentURI));
		currentURI->GetSpec(aString);
		return wxString::FromAscii(aString.get());
	}
	return wxEmptyString;
}

bool wxMozillaBrowser::Find(const wxString &searchString, bool matchCase, bool matchWholeWord, bool wrapAround, bool searchBackwards)
{
	nsCOMPtr<nsIWebBrowserFind> finder(do_GetInterface(m_Mozilla->mWebBrowser));
	if (!finder)
		return FALSE;

    nsString txtSearch = wxString_to_nsString(searchString, wxConvLocal);
    finder->SetSearchString(txtSearch.get());

	if (matchCase)
		finder->SetMatchCase(PR_TRUE);
	else
		finder->SetMatchCase(PR_FALSE);

	if (matchWholeWord)
		finder->SetEntireWord(PR_TRUE);
	else
		finder->SetEntireWord(PR_FALSE);

	if (wrapAround)
		finder->SetWrapFind(PR_TRUE);
	else
		finder->SetWrapFind(PR_FALSE);

	if (searchBackwards)
		finder->SetFindBackwards(PR_TRUE);
	else
		finder->SetFindBackwards(PR_FALSE);

	PRBool result;
	finder->FindNext(&result);

	if (result)
		return TRUE;
	else
		return FALSE;

}

bool wxMozillaBrowser::FindNext()
{
	nsCOMPtr<nsIWebBrowserFind> finder(do_GetInterface(m_Mozilla->mWebBrowser));
	if (!finder)
		return FALSE;

	//find next means all settings are the same
	PRBool result;
	finder->FindNext(&result);

	if (result)
		return TRUE;
	else
		return FALSE;
}

wxString wxMozillaBrowser::GetSelection()
{
    nsresult rv ;
	nsCOMPtr<nsISelection> theSelection ;
	nsCOMPtr<nsIDOMWindow> theDomWindow;

	// Get the nsIDOMWindow interface in order to get nsISelection 
	rv = m_Mozilla->mWebBrowser->GetContentDOMWindow(getter_AddRefs(theDomWindow));

	// Now get the nsISelection interface
	rv = theDomWindow->GetSelection(getter_AddRefs(theSelection));
	PRUnichar* thetext;
	theSelection->ToString(&thetext);
	if (thetext)
    {
		nsString aString(thetext);
		return nsString_to_wxString(aString, wxConvLocal);
    }
    else
        return wxEmptyString;

}
    
/**
 * Goes to URL previously visited
 *
 * @return
 * 	True
 */
bool wxMozillaBrowser::GoBack()
{
	if(m_Mozilla->mWebNav)
		m_Mozilla->mWebNav->GoBack();

	return TRUE;
}

/**
 * Checks to determine if previous URL available
 *
 * @return
 * 	True if available, otherwise false
 */
bool wxMozillaBrowser::CanGoBack()
{
	PRBool myresult = PR_FALSE;
	if(m_Mozilla->mWebNav)
		m_Mozilla->mWebNav->GetCanGoBack(&myresult);
	
	if (myresult)
		return TRUE;
	else
		return FALSE;
}
/**
 * Go forward in history
 *
 * @return
 * 	True if successful, otherwise false
 */
bool wxMozillaBrowser::GoForward()
{
	if(m_Mozilla->mWebNav)
		m_Mozilla->mWebNav->GoForward();

	return TRUE;
}

/**
 * Checks to determine if forward address available
 *
 * @return
 * 	True if succesful, otherwise false
 */
bool wxMozillaBrowser::CanGoForward()
{
	PRBool myresult = PR_TRUE;
	if(m_Mozilla->mWebNav)
		m_Mozilla->mWebNav->GetCanGoForward(&myresult);
	
	if (myresult)
		return TRUE;
	else
		return FALSE;
}

/**
 * Stop the loading of address
 *
 * @return
 * 	True if successful, otherwise false
 */
bool wxMozillaBrowser::Stop()
{
	if(m_Mozilla->mWebNav)
		m_Mozilla->mWebNav->Stop(nsIWebNavigation::STOP_ALL);

	return TRUE;
}

/**
 * Reload current address
 *
 * @return
 * 	True if successful, otherwise false
 */
bool wxMozillaBrowser::Reload()
{
	if(m_Mozilla->mWebNav)
		m_Mozilla->mWebNav->Reload(nsIWebNavigation::LOAD_FLAGS_NONE);
		
	return TRUE;
}

bool wxMozillaBrowser::SavePage(const wxString &filename, bool saveFiles)
{
	//Works, but has troubles with frames pages
	int extensionStart;
	char ext = '.';
	extensionStart = filename.Find(ext, TRUE);
	wxString fileFolder = filename.Mid(0, extensionStart);
	fileFolder << _T("_files");
        // Save the file
        nsCOMPtr<nsIWebBrowserPersist> persist(do_QueryInterface(m_Mozilla->mWebBrowser));
        if(persist)
        {
			PRUint32 currentState;
			persist->GetCurrentState(&currentState);
			if (currentState == nsIWebBrowserPersist::PERSIST_STATE_SAVING)
				return FALSE; //still performing a previous save - can't save again
            nsCOMPtr<nsILocalFile> file;
            NS_NewNativeLocalFile(nsDependentCString(filename.mb_str(wxConvFile)), PR_TRUE, getter_AddRefs(file));

            nsCOMPtr<nsILocalFile> dataPath;
            NS_NewNativeLocalFile(nsDependentCString(fileFolder.mb_str(wxConvFile)), PR_TRUE, getter_AddRefs(dataPath));
            PRUint32 flags;
            persist->GetPersistFlags( &flags );
            if( !(flags & nsIWebBrowserPersist::PERSIST_FLAGS_REPLACE_EXISTING_FILES ) ) 
                persist->SetPersistFlags( nsIWebBrowserPersist::PERSIST_FLAGS_REPLACE_EXISTING_FILES );
            if (saveFiles)
            persist->SaveDocument(nsnull, file, dataPath, nsnull, 0, 0);
            else
			{
				//Hack for a weird Mozilla bug - if you pass nsnull for the dataPath
				//property, (meaning just save the HTML) it will finish saving properly 
				//but internally the save operation is never marked as finished. We need 
				//to explicitly tell it to cancel the (finished) save before we can save again.
				//Make sense? Didn't think so. But it works! =)
				if (currentState == nsIWebBrowserPersist::PERSIST_STATE_READY)
					persist->CancelSave();
                persist->SaveDocument(nsnull, file, nsnull, nsnull, 0, 0);
			}
                //persist->SaveCurrentURI(file);
        }
	return TRUE;
}

/**
  * Sets content of page to data
  *
  * @param data
  *         String data to be set as page content
  *
  * @return
  *         True on success, False on failure
  */
bool wxMozillaBrowser::SetPage(const wxString &data)
{
	//if we're in editing mode, we don't want to reload
	//from stream because it loses its path information
	//and thus external links break

	// create stream to put string in
	nsCOMPtr<nsIInputStream> inputStream;

	    // convert our string to stream
	    nsresult rv =
		NS_NewCStringInputStream(getter_AddRefs(inputStream),
		                         nsCString(data.mb_str(wxConvUTF8)));
			if (NS_FAILED(rv)) return FALSE;

			// get document shell
			nsCOMPtr<nsIDocShell> docShell(do_GetInterface(m_Mozilla->mWebBrowser));
			NS_ENSURE_TRUE(docShell, NS_ERROR_FAILURE);

    // finally, load the stream we made!
    rv = docShell->LoadStream(inputStream,
                              NULL /*URI*/,
                              NS_LITERAL_CSTRING("text/html"),
#if wxUSE_UNICODE
                              NS_LITERAL_CSTRING("UTF-8"),
#else
                              nsCAutoString(wxLocale::GetSystemEncodingName()),
#endif
                              NULL /*loadInfo*/);
			if(NS_FAILED(rv)) return FALSE;

        return TRUE;
}

/**
  * Gets content of current page
  *
  * @return
  *         Content of current page, or emptry string on error
  */

wxString wxMozillaBrowser::GetPage()
{
        nsresult rv;
        nsString docStr;
        // get dom document from web nav
        nsCOMPtr<nsIDOMDocument> domDocument;
        rv = m_Mozilla->mWebNav->GetDocument(getter_AddRefs(domDocument));
        
        if (NS_FAILED(rv)) return wxEmptyString;
        if (!domDocument) return wxEmptyString;

        // get document from dom document
        nsCOMPtr<nsIDocument> document(do_QueryInterface(domDocument));

        // create document encoder to turn document into string
        nsCOMPtr<nsIDocumentEncoder> docEncoder;
        docEncoder = do_CreateInstance(NS_DOC_ENCODER_CONTRACTID_BASE
"text/html");
        
        docEncoder->Init(document, NS_LITERAL_STRING("text/html"), 0);
        docEncoder->EncodeToString(docStr);
        return nsString_to_wxString(docStr, wxConvLocal);
}

/**
 * Get hyperlink link message
 *
 * @return
 * 	String containing message
 */
wxString wxMozillaBrowser::GetLinkMessage()
{
	return wxEmptyString;
}

/**
 * Get Javascript status
 *
 * @return
 * 	String containing message
 */
wxString wxMozillaBrowser::GetJSStatus()
{
	return wxEmptyString;
}

/**
 * @author David Teller <Yoric@users.sourceforge.net>
 * Sets the zoom level
 */
bool wxMozillaBrowser::SetZoom(float level)
{
  nsCOMPtr<nsIDocShell> doc_shell(do_GetInterface(m_Mozilla->mWebBrowser));
  NS_ENSURE_TRUE(doc_shell, false);
  
  nsCOMPtr<nsIContentViewer> content_viewer;
  doc_shell->GetContentViewer(getter_AddRefs(content_viewer));
  NS_ENSURE_TRUE(content_viewer, false);

  nsCOMPtr<nsIMarkupDocumentViewer> markup_document_viewer = do_QueryInterface(content_viewer);
  NS_ENSURE_TRUE(markup_document_viewer, false);

  nsresult rv = markup_document_viewer->SetTextZoom(level);
  NS_ENSURE_TRUE(NS_SUCCEEDED(rv), false);


  return true;
}

	/**
 * @author David Teller <Yoric@users.sourceforge.net>
 *
 * Returns a pointer to the current document
 * @warning behaviour is non-specified if the current document is not fully loaded !
 */
bool wxMozillaBrowser::GetDOMDocument(nsIDOMDocument** aDocument)
{
  nsresult rv = m_Mozilla->mWebNav->GetDocument(aDocument);
  return NS_SUCCEEDED(rv);
}


#ifdef __WXMSW__
/**
 * @author Zhang Yue <zhangyue99@tsinghua.org.cn>
 * we need to override wx set focus method here
 */
void wxMozillaBrowser::SetFocus()
{
        m_Mozilla->mBaseWindow->SetFocus(); // set focus
        nsCOMPtr<nsIWebBrowserFocus> browserAsFocus = do_QueryInterface(m_Mozilla->mWebBrowser);
        if (browserAsFocus)                               // if possible
            browserAsFocus->Activate();             // activate window (cursor)
}
#endif




class wxMozillaModule: public wxModule
{
DECLARE_DYNAMIC_CLASS(wxMozillaModule)
public:
    wxMozillaModule() {}
    bool OnInit()
    {
		//let wxMozilla classes run the wxMozilla startup code
        return TRUE;
    }
    void OnExit()
    {
        wxMozillaShutdown();
    }
};

IMPLEMENT_DYNAMIC_CLASS(wxMozillaModule, wxModule)

void wxMozillaInitResourceModule()
{
    wxModule* module = new wxMozillaModule;
    module->Init();
    wxModule::RegisterModule(module);
}
