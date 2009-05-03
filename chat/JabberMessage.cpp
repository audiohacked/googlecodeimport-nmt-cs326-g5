#include <QtGui>
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

ChatMsgSess::ChatMsgSess(ChatContactItemData *c, QObject *parent)
:QObject(parent)
{
	contact = c;
	m_client = c->conn;
	c->conn->registerMessageSessionHandler( this, 0 );
}

void ChatMsgSess::handleMessageSession( MessageSession *msgSes )
{
	qDebug() << "ChatMsgSess handleMessageSession";

	// this example can handle only one session. so we get rid of the old session
	if (m_session)
		m_client->disposeMessageSession( m_session );
	m_session = msgSes;
	m_session->registerMessageHandler( this );
	
	// the following is optional
	//m_messageEventFilter = new MessageEventFilter( m_session );
	//m_messageEventFilter->registerMessageEventHandler( this );
	//m_chatStateFilter = new ChatStateFilter( m_session );
	//m_chatStateFilter->registerChatStateHandler( this );

}

void ChatMsgSess::handleMessage( const Message &msg, MessageSession *msgSes )
{
	QString from = QString::fromStdString(msgSes->target().username());
	QString text = QString::fromStdString(msg.body());
	qDebug() << "handle incomming Messages:" << from << "; has Win?: "<< contact->hasWin;
	if (contact->hasWin)
	{
		//contact->win->show();
		contact->win->chatText->append("incomming");
	}
	/*else
	{

		QThread *currthread = thread();
		moveToThread(qApp->thread());
		//contact->win = new ChatWindowChat(contact);
		moveToThread(currthread);
		//contact->win->show();
	}*/

}

void ChatMsgSess::handleMessageEvent(const JID &jid, MessageEventType MsgEvent)
{
	qDebug() << "display contact's Message Event";
}

void ChatMsgSess::handleChatState( const JID &jid, ChatStateType ChatState)
{
	qDebug() << "display contact's Chat State";
}

MessageSession* ChatMsgSess::newSession( const JID& to )
{
	qDebug() << "newSession";
	MessageSession* session = new MessageSession( m_client, to );
	session->registerMessageHandler( this );
	return session;
}
