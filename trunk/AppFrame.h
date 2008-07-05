#ifndef __APP_FRAME_H
#define __APP_FRAME_H

	#include <wx/frame.h>
	#include <wx/treectrl.h>

	#include "AppMenu.h"
	#include "AppPanel.h"
#ifdef CHAT_ENABLED
	#include "ChatConnectionThread.h"
	#include "ChatRoster.h"
	#include "ChatMessage.h"
#endif
	
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
			void OnMenuAddTorrent(wxCommandEvent& event);
			void OnMenuAddHttpDownload(wxCommandEvent& event);
			void OnIconize(wxIconizeEvent& event);
			
			DDPSMenu *menu;
			DDPSPanel *panel;
			
#ifdef CHAT_ENABLED
			void InitChat();
			wxTreeCtrl *rosterList;
			ChatConnThread *thread;
			ChatWindowRoster *chat;
			ChatRoster *rosterListener;
			ChatMsgSess *cMsg;
			//ChatAccount *cAccount;
#endif
		
		DECLARE_EVENT_TABLE()
	};

#endif
