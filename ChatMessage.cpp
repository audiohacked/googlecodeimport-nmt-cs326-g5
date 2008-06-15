//#include "ChatApp.h"
#include "common.h"
#include "ChatCommon.h"
#include "ChatMessage.h"
#include "ChatRosterData.h"

/**
new incoming chat:
	loop through wxTreeCtrl to see if one exsits
new outgoing chat:
	loop through wxTreeCtrl to see if one exsits
on app close:
	loop through wxTreeCtrl and close windows and sessions; clean up

// user is typing a message
m_messageEventFilter->raiseMessageEvent( MessageEventComposing );
// acknowledge receiving of a message
m_messageEventFilter->raiseMessageEvent( MessageEventDelivered );
// user is not actively paying attention to the chat
m_chatStateFilter->setChatState( ChatStateInactive );
// user has closed the chat window
m_chatStateFilter->setChatState( ChatStateGone );
*/

ChatMsgSess::ChatMsgSess(Client *conn) {
	m_client = conn;
	conn->registerMessageSessionHandler( this, 0 );
}

void ChatMsgSess::handleMessageSession( MessageSession *msgSes )
{
/*
	check for new chat: loop thru list
	if new chat: create new window and session
*/

	wxLogMessage(wxT( "got new session\n"));
	// this example can handle only one session. so we get rid of the old session
	m_client->disposeMessageSession( m_session );
	m_session = msgSes;
	m_session->registerMessageHandler( this );
	m_messageEventFilter = new MessageEventFilter( m_session );
	m_messageEventFilter->registerMessageEventHandler( this );
	m_chatStateFilter = new ChatStateFilter( m_session );
	m_chatStateFilter->registerChatStateHandler( this );

}

void ChatMsgSess::handleMessage( const Message &msg, MessageSession *msgSes )
{
	DDPS &myApp = ::wxGetApp();
	wxTreeItemId root=myApp.chat->panel->listRoot;
	wxTreeCtrl *list = myApp.chat->panel->list;
	wxTreeItemId itemId;
	
	wxString who = gloox2wxString(msg.from().bare());
	wxString username = gloox2wxString(msg.from().username());
	wxString text = gloox2wxString(msg.body());

	wxTreeItemIdValue cookie;
	itemId = findTreeItem(list,
		list->GetFirstChild(root, cookie),
		who);

	ChatContactItemData *item = (ChatContactItemData *)list->GetItemData(itemId);
/*	if (itemId.IsOk())
	{*/
		wxMutexGuiEnter();

		if (item->name == wxT(""))
			item->win->panel->chatText->AppendText(username + wxT(": ") + text + wxT("\n"));
		else
			item->win->panel->chatText->AppendText(item->name + wxT(": ") + text + wxT("\n"));

		if (item->win->IsShown())
		{
			wxLogMessage(wxT("incomming message; window is showing"));
		}
		else
		{
			wxLogMessage(wxT("imcomming message; window is not showing"));
			item->win->Show(TRUE);			
		}

		wxMutexGuiLeave();
/*	}
	else
	{
		wxLogMessage(  wxT("msg from: ")+who+wxT(" body: ")+text  );
	}*/
}

void ChatMsgSess::handleMessageEvent(const JID &jid, MessageEventType MsgEvent)
{
	/*display contact's Message Event*/
}

void ChatMsgSess::handleChatState( const JID &jid, ChatStateType ChatState)
{
	/*display contact's Chat State*/
}

MessageSession* ChatMsgSess::newSession( const JID& to )
{
	wxLogMessage( wxT("newSession with jid: ") + gloox2wxString(to.full()));
	MessageSession* session = new MessageSession( m_client, to );
	session->registerMessageHandler( this );
	return session;
}
