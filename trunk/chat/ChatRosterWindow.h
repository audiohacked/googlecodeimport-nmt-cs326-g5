#ifndef __CHAT_ROSTER_WINDOW_H
#define __CHAT_ROSTER_WINDOW_H
	class ChatWindowRosterPanel : public wxPanel
	{
		public:
			ChatWindowRosterPanel(wxWindow *parent, wxWindowID id, Client *conn);
			void AddContact(wxString contact, JID jid);
			void NewChatWindow(wxTreeEvent &event);
			wxTreeCtrl *list;
			wxTreeItemId listRoot;
			Client *j;
		DECLARE_EVENT_TABLE()
	};

	class ChatWindowRoster : public wxFrame
	{
		public:
			ChatWindowRoster(Client *conn);
			virtual ~ChatWindowRoster();
			ChatWindowRosterPanel *panel;
		private:
			Client *j;
	};

#endif