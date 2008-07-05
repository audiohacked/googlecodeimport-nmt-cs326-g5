	#include <wx/wxprec.h>
	#ifndef WX_PRECOMP
		#include <wx/wx.h>
	#endif

	#include <wx/utils.h>
	#include <wx/choicebk.h>

	#include <wx/notebook.h>
	#include <wx/panel.h>
	#include <wx/aboutdlg.h>
	#include <wx/generic/aboutdlgg.h>
	#include <wx/treectrl.h>
	
	#include "config.h"

	#include "AppMenu.h"
	#include "AppLogin.h"
	#include "BrowserEmbed.h"
	#include "TransferManager.h"
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
#include "AppFrame.h"

// Event Table for frame - used for menu
BEGIN_EVENT_TABLE( DDPSFrame, wxFrame )
	EVT_ICONIZE(DDPSFrame::OnIconize)

	EVT_MENU(MENU_Quit, DDPSFrame::OnExit) /* when we click Quit in the menu system this event closes	the window and cleans up */
	EVT_MENU(MENU_About, DDPSFrame::AboutBox) /* when we click Help->About_This_App this event opens the about box */
	EVT_MENU(MENU_Support, DDPSFrame::GoToSupportPanel)
	EVT_MENU(MENU_Settings, DDPSFrame::SettingsDialog) // open the settings dialog when file->settings is clicked
	EVT_MENU(MENU_Home, DDPSFrame::GotoHomepage)
	EVT_MENU(MENU_Community, DDPSFrame::GotoCommunity)
	EVT_MENU(MENU_Downloads, DDPSFrame::GotoDownloads)
	EVT_MENU(MENU_Logout, DDPSFrame::Logout)
	
	EVT_MENU(MENU_TorrentDownload, DDPSFrame::OnMenuAddTorrent)
	EVT_MENU(MENU_HTTPDownload, DDPSFrame::OnMenuAddHttpDownload)
	
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

void DDPSFrame::OnMenuAddTorrent(wxCommandEvent &event)
{
	panel->tabs->Downloads->OnMenuAddTorrent(event);
}

void DDPSFrame::OnMenuAddHttpDownload(wxCommandEvent &event)
{
	panel->tabs->Downloads->OnMenuAddHttpDownload(event);
}

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
