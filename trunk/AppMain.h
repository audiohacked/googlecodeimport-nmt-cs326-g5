#ifndef __APP_MAIN_H
#define __APP_MAIN_H
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
	
#ifdef CHAT_ENABLED
	#include "ChatConnectionThread.h"
	#include "ChatRoster.h"
	#include "ChatMessage.h"
#endif
	

	class DDPSTabbed : public wxNotebook
	{
		public:
			DDPSTabbed(wxWindow *parent, wxWindowID id, const wxPoint &pos, const wxSize &size, long style);
			DDPSBrowser *Home;
			DDPSBrowser *Community;
			wxWindow *wParent;

			DECLARE_EVENT_TABLE()
	};
	
	class DDPSPanel : public wxPanel
	{
		public:
			DDPSPanel(wxWindow *parent, wxWindowID id, const wxPoint &pos, const wxSize &size, long style);

			void GotoNewsTab(wxCommandEvent&);
			void GotoSupport(wxCommandEvent&);
			void GotoHomepage(wxCommandEvent& event);
			void GotoCommunity(wxCommandEvent& event);
			void GotoDownloads(wxCommandEvent& event);
			void ChatRosterOpen(wxCommandEvent& event);
			DDPSTabbed *tabs;
			wxWindow *wParent;
			
			DECLARE_EVENT_TABLE()
	};
	
	class DDPSFrame : public wxFrame
	{
		public:
			DDPSFrame(const wxString &title, const wxPoint &pos, const wxSize &size);
			void OnExit( wxCommandEvent &event);
			void AboutBox(wxCommandEvent &event);
			void SettingsDialog(wxCommandEvent &event);
			void GoToSupportPanel(wxCommandEvent &event);
			void GotoHomepage(wxCommandEvent& event);
			void GotoCommunity(wxCommandEvent& event);
			void GotoDownloads(wxCommandEvent& event);
			void Logout(wxCommandEvent& event);
			DDPSMenu *menu;
			DDPSPanel *panel;
			wxWindow *wParent;
			wxTreeCtrl *rosterList;
			
#ifdef CHAT_ENABLED
			void InitChat();
			ChatConnThread *thread;
			ChatWindowRoster *chat;
			ChatRoster *rosterListener;
			ChatMsgSess *cMsg;
			//ChatAccount *cAccount;
#endif
		
		DECLARE_EVENT_TABLE()
	};

#endif
