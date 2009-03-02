	#include <wx/wxprec.h>
	#ifndef WX_PRECOMP
		#include <wx/wx.h>
	#endif

	#include <wx/utils.h>
	#include <wx/choicebk.h>

	#include <wx/notebook.h>
	#include <wx/panel.h>
	//#include <wx/aboutdlg.h>
	//#include <wx/generic/aboutdlgg.h>
	#include <wx/treectrl.h>
	
	#include "config.h"

	#include "AppMenu.h"
	#include "AppLogin.h"
#ifdef BUILTIN_BROWSER
    #include "BrowserEmbed.h"
#endif

#ifdef DOWNLOADER
	#include "TransferManager.h"
#endif
	#include "SettingsDialog.h"
	#include "AppConfig.h"
	
#ifdef CHAT_ENABLED
	#include "ChatCommon.h"
	#include "ChatConnectionThread.h"
	#include "ChatRoster.h"
	#include "ChatMessage.h"
#endif

#include "AppEnum.h" // needed for the MENU_Quit and etc.
#include "AppLogin.h"
#include "AppMain.h"

#include "AppUpdate.h"

#include "AppFrame.h"

#if !defined(__WXMSW__) && !defined(__WXPM__)
    #include "ddps.xpm"
#endif

// Event Table for frame - used for menu
BEGIN_EVENT_TABLE( DDPSFrame, wxFrame )
	EVT_ICONIZE(DDPSFrame::OnIconize)

	EVT_MENU(MENU_Quit, DDPSFrame::OnExit) /* when we click Quit in the menu system this event closes	the window and cleans up */
#ifdef BROKEN_ABOUTBOX
	EVT_MENU(MENU_About, DDPSFrame::AboutBox) /* when we click Help->About_This_App this event opens the about box */
#endif /* BROKEN_ABOUTBOX */
	EVT_MENU(MENU_Support, DDPSFrame::GoToSupportPanel)
	EVT_MENU(MENU_Settings, DDPSFrame::SettingsDialog) // open the settings dialog when file->settings is clicked
#ifdef BUILTIN_BROWSER
	EVT_MENU(MENU_Home, DDPSFrame::GotoHomepage)
	#ifdef COMMUNITY_PORTAL
	EVT_MENU(MENU_Community, DDPSFrame::GotoCommunity)
	#endif /* COMMUNITY_PORTAL */
#endif /* BUILTIN_BROWSER */

	EVT_MENU(MENU_Logout, DDPSFrame::Logout)
#ifdef DOWNLOADER
    #ifdef TORRENT	
	EVT_MENU(MENU_TorrentDownload, DDPSFrame::OnMenuAddTorrent)
    #endif /* TORRENT */
	EVT_MENU(MENU_Downloads, DDPSFrame::GotoDownloads)
	EVT_MENU(MENU_HTTPDownload, DDPSFrame::OnMenuAddHttpDownload)
#endif /* DOWNLOADER */

#ifdef UPDATER	
	EVT_MENU(MENU_Update, DDPSFrame::OnUpdateCheck)
	//EVT_MENU(Minimal_LocalCheck, MyFrame::OnLocalCheck)
#endif
END_EVENT_TABLE()

#ifdef CHAT_ENABLED
void DDPSFrame::InitChat()
{
	rosterListener = new ChatRoster( thread->server->FetchConnection() );
	cMsg = new ChatMsgSess( thread->server->FetchConnection() );
	//cAccount = new ChatAccount( thread->server->FetchConnection() );
}
#endif

DDPSFrame::DDPSFrame(const wxString &title, const wxPoint &pos, const wxSize &size)
: wxFrame((wxFrame*) NULL, WINDOW_Frame, title, pos, size, wxDEFAULT_FRAME_STYLE, wxT("DDPS"))
{
	SetIcon(wxICON(ddps));
    
	bool LoginOk = false;
	CreateStatusBar(3);
	SetStatusText(wxT("Ready!"), 0);
	DDPSMenu *menu = new DDPSMenu();
	SetMenuBar(menu);
	panel = new DDPSPanel(this, -1, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL|wxNO_BORDER);
#ifdef DEVEL_TESTING
	panel->SetFocus();
#else
	AppLogin *login = new AppLogin();
	if(login->DoLogin())
	{
		wxGetApp().LoginUsername = login->GetUsername();
		wxGetApp().LoginPassword = login->GetPassword();
		//SetStatusText(wxGetApp().LoginUsername, 1);
		//SetStatusText(wxGetApp().LoginPassword, 2);
		wxLogMessage(wxT("Welcome user: ") + wxGetApp().LoginUsername);

	#ifdef CHAT_ENABLED
		thread = new ChatConnThread();
		InitChat();
		thread->Run();
		chat = new ChatWindowRoster(thread->server->FetchConnection());
	#endif

		panel->SetFocus();
	}
	else
	{
		Close(TRUE);
	}
#endif
}

#ifdef TORRENT
void DDPSFrame::OnMenuAddTorrent(wxCommandEvent &event)
{
	panel->tabs->Downloads->OnMenuAddTorrent(event);
}
#endif

#ifdef DOWNLOADER
void DDPSFrame::OnMenuAddHttpDownload(wxCommandEvent &event)
{
	panel->tabs->Downloads->OnMenuAddHttpDownload(event);
}
#endif

void DDPSFrame::OnExit(wxCommandEvent& event)
{
#ifdef CHAT_ENABLED
	thread->server->FetchConnection()->rosterManager()->removeRosterListener();
	thread->server->FetchConnection()->disposeMessageSession(cMsg->m_session);
	chat->panel->list->DeleteAllItems();
	thread->server->FetchConnection()->disconnect();
	//thread->Delete();
#endif
	Close(TRUE);
}

#ifdef BROKEN_ABOUTBOX
void DDPSFrame::AboutBox(wxCommandEvent& WXUNUSED(event))
{
	DDPS &myApp = ::wxGetApp();
	wxLogMessage(wxT("Aboutbox: ") + myApp.LoginUsername);
		wxAboutDialogInfo info;
		info.SetName(wxT("DDPS"));
		info.SetVersion(wxT("1.0 Beta"));
		info.SetDescription(wxT("This Program is a Digital Content Distribution and Publishing System. Written Spring 2008 for CS326: Software Engineering."));
		info.SetCopyright(wxT("(C) 2008 Sean Nelson <snelson@nmt.edu>, Josha Barron <jbarron@nmt.edu>, Corey Brown <coreyb42@gmail.com>, Adam Troemne <atroemne@nmt.edu>"));
	#ifdef __WXGTK__
		//wxAboutBox(info);
	#else
		wxAboutBox(info);
	#endif
}
#endif

void DDPSFrame::GoToSupportPanel(wxCommandEvent& event)
{
	panel->GotoSupport(event);
}

void DDPSFrame::GotoHomepage(wxCommandEvent& event)
{
	panel->GotoHomepage(event);
}

void DDPSFrame::GotoCommunity(wxCommandEvent& event)
{
	panel->GotoCommunity(event);
}

void DDPSFrame::GotoDownloads(wxCommandEvent& event)
{
	panel->GotoDownloads(event);
}

void DDPSFrame::Logout(wxCommandEvent& event)
{
	AppLoginDialog loginDlg(this, -1, wxT("User Login"), wxDefaultPosition, wxDefaultSize);
	if(loginDlg.ShowModal() == wxID_OK)
	{
		panel->SetFocus();
	} else {
		Close(TRUE);
	}
}

//open the settings dialog
void DDPSFrame::SettingsDialog(wxCommandEvent& event)
{
	SettingsFrame settingsFrame(this, -1, wxT("Settings"),wxDefaultPosition, wxSize(800,600));
	settingsFrame.ShowModal();
	//settingsFrame->Show(TRUE);
}

void DDPSFrame::OnIconize(wxIconizeEvent& event)
{
	if (event.Iconized())
	{
		this->Show(FALSE);
	}
	else
	{
		this->Show(TRUE);
	}
}


void DDPSFrame::OnUpdateCheck(wxCommandEvent &)
{
	wxUpdateAndExit(this, TRUE, TRUE, wxEmptyString, wxEmptyString, wxEmptyString, 
 						wxT("http://" UPDATEURL "/updates.xml"));
}

void DDPSFrame::OnLocalCheck(wxCommandEvent &)
{
	// for --uri option you must use an absolute path or 
 	// a path relative to the local.xml file
 	// (for te --xml and --xrc option, a path relative to the 
  	//  WebUpdater executable location must be used)

	//wxUpdateAndExit(this, TRUE, TRUE, wxEmptyString, wxEmptyString, wxEmptyString, 
 	//					wxT("file:../../../website/script3.xml"));
}