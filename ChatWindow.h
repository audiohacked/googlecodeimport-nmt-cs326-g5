#ifndef __CHAT_WINDOW_H
#define __CHAT_WINDOW_H

	#include <wx/wxprec.h>
	#ifndef WX_PRECOMP
		#include <wx/wx.h>
	#endif
	
	#include <wx/treectrl.h>
		
	#include <client.h>
	#include <gloox.h>
	using namespace gloox;
	
	#include "ChatMessage.h"
		
	class ChatWindowChatPanel : public wxPanel
	{
		public:
			ChatWindowChatPanel(wxWindow *parent, wxWindowID id, wxTreeCtrl *list, wxTreeItemId itemId);
			void SendMsg(wxCommandEvent &event);
			void TextChanged(wxCommandEvent &event);
			wxTreeCtrl *contact_list;
			wxTreeItemId contact_id;
			wxTextCtrl *chatText;
			wxTextCtrl *sendText;
			wxButton *sendButton;
			ChatMsgSess *chatSes;
		DECLARE_EVENT_TABLE()
	};
	
	class ChatWindowChat : public wxFrame
	{
		public:
			ChatWindowChat(wxTreeCtrl *list, wxTreeItemId id);
			virtual ~ChatWindowChat();
			void OnCloseWindow(wxCloseEvent& event);
			ChatWindowChatPanel *panel;
			wxTreeItemId itemId;
			wxTreeCtrl *rosterList;
		DECLARE_EVENT_TABLE()
	};
	
/*	
	class ChatWindowGroupChat : public wxFrame
	{
		public:
			ChatWindowGroupChat(){}
			
	};
*/
#endif
	