#include "AppMain.h"

#include "enum.h" // needed for the MENU_Quit and etc.

/* we have here is the event table used for event handling
	I still have no idea how this works
	*/
BEGIN_EVENT_TABLE( sAppFrame, wxFrame )
	EVT_MENU(MENU_Quit, sAppFrame::OnExit) /* when we click Quit in the menu system this event closes	the window and cleans up */
	EVT_MENU(MENU_About, sAppFrame::AboutBox) /* when we click Help->About_This_App this event opens the about box */
	EVT_MENU(MENU_Support, sAppPanel::GotoSupport)
	EVT_MENU(MENU_About, sAppPanel::GotoSettings)
END_EVENT_TABLE()

BEGIN_EVENT_TABLE( sAppTabbed, wxNotebook )
	//EVT_NOTEBOOK_PAGE_CHANGED(wxID_ANY, sAppTabbed::OnNotebook)
	//EVT_NOTEBOOK_PAGE_CHANGING(wxID_ANY, sAppTabbed::OnNotebook)
END_EVENT_TABLE()

BEGIN_EVENT_TABLE( sAppPanel, wxPanel )
	EVT_BUTTON(TABB_News, sAppPanel::GotoNewsTab)
	EVT_BUTTON(TABB_Support, sAppPanel::GotoSupport)
	EVT_BUTTON(TABB_Settings, sAppPanel::GotoSettings)
END_EVENT_TABLE()

IMPLEMENT_APP(sApp)

bool sApp::OnInit()
{
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
				tabs->Home->browser->LoadURL(wxT(HOMEPAGE));
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
				tabs->Home->browser->LoadURL(wxT(SUPPORTPAGE));
			}
			tabs->ChangeSelection(0);
		}
	#else
	
	#endif
	
}

void sAppPanel::GotoSettings(wxCommandEvent& WXUNUSED(event))
{
	#ifdef BUILTIN_BROWSER
		if ( tabs )
		{
			if (tabs->Home->browser)
			{
				tabs->Home->browser->LoadURL(wxT("http://coreyb.homelinux.org/contentmanager/support/"));
			}
			tabs->ChangeSelection(0);
		}
	#endif
}

sAppTabbed::sAppTabbed(wxWindow *parent, wxWindowID id, const wxPoint &pos,
	 const wxSize &size, long style) : wxNotebook(parent, id, pos, size, style)
{
	#ifdef BUILTIN_BROWSER
		Home = new sAppBrowser(this, TABPAGE_Browser, wxDefaultPosition,
			wxDefaultSize);
		Home->home = wxT(HOMEPAGE);
		Home->GotoHomepage();
		AddPage(Home, _T("Browser"));
	#endif
	
	#ifdef COMMUNITY_PORTAL
		Community = new sAppBrowser(this, TABPAGE_Community, 
			wxDefaultPosition, wxDefaultSize);
		Community->home = wxT(COMMUNITYPAGE);
		Community->GotoHomepage();
		AddPage(Community, _T("Community"));
	#endif

	#ifdef DOWNLOAD_PANEL
		wxPanel *Downloads = new sAppDownloadsPanel(this, -1, wxDefaultPosition, 
			wxDefaultSize, wxTAB_TRAVERSAL|wxCLIP_CHILDREN|wxNO_BORDER);
		AddPage(Games, _T("Downloads"));
	#endif
}
