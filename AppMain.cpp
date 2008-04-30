#include "AppMain.h"

#include "enum.h" // needed for the MENU_Quit and etc.

/* we have here is the event table used for event handling
	I still have no idea how this works
	*/
	
// Event Table for frame - used for menu
BEGIN_EVENT_TABLE( sAppFrame, wxFrame )
	EVT_MENU(MENU_Quit, sAppFrame::OnExit) /* when we click Quit in the menu system this event closes	the window and cleans up */
	EVT_MENU(MENU_About, sAppFrame::AboutBox) /* when we click Help->About_This_App this event opens the about box */
	EVT_MENU(MENU_Support, sAppPanel::GotoSupport)
	EVT_MENU(MENU_Settings, sAppFrame::SettingsDialog) // open the settings dialog when file->settings is clicked
END_EVENT_TABLE()

BEGIN_EVENT_TABLE( sAppTabbed, wxNotebook )
	//EVT_NOTEBOOK_PAGE_CHANGED(wxID_ANY, sAppTabbed::OnNotebook)
	//EVT_NOTEBOOK_PAGE_CHANGING(wxID_ANY, sAppTabbed::OnNotebook)
END_EVENT_TABLE()

// Event table for sAppPanel buttons at the bottom of the program
BEGIN_EVENT_TABLE( sAppPanel, wxPanel )
	EVT_BUTTON(TABB_News, sAppPanel::GotoNewsTab)
	EVT_BUTTON(TABB_Support, sAppPanel::GotoSupport)
	EVT_BUTTON(TABB_Settings, sAppFrame::SettingsDialog)
END_EVENT_TABLE()

IMPLEMENT_APP(sApp)

bool sApp::OnInit()
{
	#ifdef __DDPS_PROTOCOL_H
		wxFileSystem::AddHandler(new wxInternetFSHandler());
		wxFileSystem::AddHandler(new wxZipFSHandler());
		wxFileSystem::AddHandler(new wxMemoryFSHandler());
	#endif
	
	#ifdef __DDPS_PROTOCOL_H
		const wxUId id = {(wxUint32)0x8a2bcf71,(wxUint16)0x3f5b,(wxUint16)0x4559,
			{(wxUint8)0x89, (wxUint8)0x0f,(wxUint8)0xf3,(wxUint8)0xc2,(wxUint8)0xe9,(wxUint8)0x8e,
			(wxUint8)0xa7,(wxUint8)0x01}};
		wxRegisterProtocolHandler(wxT("The DDPS protocol handler"), wxT("ddps"), id, &(ddpsProtocolHandler::Create));
	#endif
	
	sAppFrame *frame = new sAppFrame(_T("sAppFrame"), wxPoint(50, 50), wxSize(800,600));
	frame->Show(TRUE);
	SetTopWindow(frame);
	return TRUE;
}

sAppFrame::sAppFrame(const wxString &title, const wxPoint &pos, const wxSize &size)
: wxFrame((wxFrame*) NULL, -1, title, pos, size)
{
	CreateStatusBar(2);
	SetStatusText(wxT("Ready!"), 0);
	sAppMenu *menu = new sAppMenu();
	SetMenuBar(menu);
	sAppPanel *panel = new sAppPanel(this, -1, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL|wxNO_BORDER);
	panel->SetFocus();
}

void sAppFrame::OnExit(wxCommandEvent &event)
{
	Close(TRUE);
}

void sAppFrame::AboutBox(wxCommandEvent& WXUNUSED(event))
{
	#ifdef __WXMAC__
		//wxAboutDialogInfo info;
		//info.SetName(_("wxSeanApp"));
		//info.SetVersion(_("1.0 Beta"));
		//info.SetDescription(_("This Program is a Digital Content Distribution and Publishing System."));
		//info.SetCopyright(_("(C) 2008 Sean Nelson <snelson@nmt.edu>")):
		//wxAboutBox(info);
	#endif
}

//open the settings dialog
void sAppFrame::SettingsDialog(wxCommandEvent& WXUNUSED(event))
{
	sSettingsFrame *settingsFrame = new sSettingsFrame(_T("Settings"), wxPoint(50, 50), wxSize(400,300));
	settingsFrame->Show(TRUE);
}

sAppPanel::sAppPanel(wxWindow *parent, wxWindowID id, const wxPoint &pos,
	const wxSize &size, long style) : wxPanel(parent, id, pos, size, style)
{
	tabs = new sAppTabbed(this, -1, wxDefaultPosition, wxDefaultSize, wxNB_FIXEDWIDTH);
	
	wxButton *News = new wxButton(this, TABB_News, wxT("News"));
	wxButton *Settings = new wxButton(this, TABB_Settings, wxT("Settings"));
	wxButton *Support = new wxButton(this, TABB_Support, wxT("Support"));
	//wxButton *InstaMessenger = new wxButton(this, -1, wxT("InstaMessenger"));

	wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer *button_sizer = new wxBoxSizer(wxHORIZONTAL);
	sizer->Add(tabs, 1, wxEXPAND|wxALL, 5);
	sizer->Add(button_sizer, 0, wxALIGN_BOTTOM, 5);
	button_sizer->Add(News, 0, wxALL, 10);
	button_sizer->Add(Settings, 0, wxALL, 10);
	button_sizer->Add(Support, 0, wxALL, 10);
	//button_sizer->Add(InstaMessenger, 0, wxALL, 10);
	SetSizer(sizer);
	sizer->SetSizeHints(this);
}

void sAppPanel::GotoNewsTab(wxCommandEvent& WXUNUSED(event))
{
	#ifdef BUILTIN_BROWSER
		if ( tabs )
		{
			if (tabs->Home->browser)
			{
				#ifdef NEWSPAGE
				tabs->Home->browser->LoadURL(wxT(NEWSPAGE));
				#else
				tabs->Home->browser->LoadURL(wxT("coreyb.homelinux.org/contentmanager/news"));
				#endif
			}
			tabs->ChangeSelection(0);
		}
	#endif
}

void sAppPanel::GotoSupport(wxCommandEvent& WXUNUSED(event))
{
	#ifdef BUILTIN_BROWSER
		if ( tabs )
		{
			if (tabs->Home->browser)
			{
				#ifdef SUPPORTPAGE
				tabs->Home->browser->LoadURL(wxT(SUPPORTPAGE));
				#else
				tabs->Home->browser->LoadURL(wxT("coreyb.homelinux.org/contentmanager/support"));
				#endif
			}
			tabs->ChangeSelection(0);
		}
	#else
	
	#endif
	
}

sAppTabbed::sAppTabbed(wxWindow *parent, wxWindowID id, const wxPoint &pos,
	 const wxSize &size, long style) : wxNotebook(parent, id, pos, size, style)
{
	#ifdef BUILTIN_BROWSER
		Home = new sAppBrowser(this, TABPAGE_Browser, 
			wxDefaultPosition, wxDefaultSize);
		#ifdef HOMEPAGE
		Home->home = wxT(HOMEPAGE);
		#else
		Home->home = wxT("coreyb.homelinux.org/contentmanager");
		#endif
		Home->GotoHomepage();
		AddPage(Home, _T("Browser"));
	#endif
	
	#ifdef COMMUNITY_PORTAL
		Community = new sAppBrowser(this, TABPAGE_Community, 
			wxDefaultPosition, wxDefaultSize);
		#ifdef COMMUNITYPAGE
		Community->home = wxT(COMMUNITYPAGE);
		#else
		Community->home = wxT("coreyb.homelinux.org/contentmanager/community");
		#endif
		Community->GotoHomepage();
		AddPage(Community, _T("Community"));
	#endif

	#ifdef __TRANSFER_MANAGER_H
		wxPanel *Downloads = new TransferManager(this, -1, wxDefaultPosition, 
			wxDefaultSize, wxTAB_TRAVERSAL|wxCLIP_CHILDREN|wxNO_BORDER);
		AddPage(Downloads, _T("Downloads"));
	#endif
}
