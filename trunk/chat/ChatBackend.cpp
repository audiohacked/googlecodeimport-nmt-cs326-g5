#include <QtGui>

#include "AppConfig.h"

#include "ChatWindow.h"
#include "ChatRosterData.h"
#include "ChatRoster.h"
#include "ChatBackend.h"

ChatRoster::ChatRoster(ChatRosterTree *t, QObject *parent)
:QObject(parent)
{
	tree = t;
	chat_connected = false;

}

void ChatRoster::exec()
{
	chat_cfg = new DDPSConfig;
	qDebug() << "ChatRoster::exec";
	std::string username = chat_cfg->cfg_LoginUsername.toStdString();
	std::string password = chat_cfg->cfg_LoginPassword.toStdString();

#ifdef CHAT_SERVER
	JID jid( username+"@"+ CHAT_SERVER +"/DDPSChat" );
#else
	JID jid( username+"@audiohacked-vista/DDPSChat" );
#endif
	conn = new Client(jid, password);

	conn->setSASLMechanisms(SaslMechPlain);

	conn->registerConnectionListener( this );
	conn->registerMessageSessionHandler( this, 0 );
	conn->registerMessageHandler( this );

	conn->rosterManager()->registerRosterListener( this );

	conn->disco()->setVersion( "ddps", "client", "test" );
	conn->disco()->setIdentity( "client", "bot" );
	
	conn->registerPresenceHandler( this );
	conn->setPresence( Presence::Available, 1 );

	conn->connect(false);
	chat_connected = true;

	t = new QTimer( this );
	connect( t, SIGNAL(timeout()), this, SLOT(processMessages()) );
	t->start(0);
}

void ChatRoster::stop()
{
	conn->disconnect();
	chat_connected = false;
	t->stop();
}

void ChatRoster::onConnect()
{
	qDebug() << "connection";
}

void ChatRoster::onDisconnect(ConnectionError e)
{
	qDebug() << "disconnection";
}

bool ChatRoster::onTLSConnect(const CertInfo& info)
{
	qDebug() << "TLS Connection";
    return true;
}

void ChatRoster::processMessages()
{
	conn->recv(0);
}

void ChatRoster::handlePresence( const Presence &presence )
{
	qDebug() << "Setting Presence";
	conn->setPresence( Presence::Available, 1 );
}
			
void ChatRoster::onResourceBindError( ResourceBindError error )
{
	printf( "onResourceBindError: %d\n", error );
}

void ChatRoster::onSessionCreateError( SessionCreateError error )
{
	printf( "onSessionCreateError: %d\n", error );
}

void ChatRoster::handleItemSubscribed( const JID& jid )
{
	printf( "subscribed %s\n", jid.bare().c_str() );
}

void ChatRoster::handleItemAdded( const JID& jid )
{
	printf( "added %s\n", jid.bare().c_str() );
}

void ChatRoster::handleItemUnsubscribed( const JID& jid )
{
	printf( "unsubscribed %s\n", jid.bare().c_str() );
}

void ChatRoster::handleItemRemoved( const JID& jid )
{
	printf( "removed %s\n", jid.bare().c_str() );
}

void ChatRoster::handleItemUpdated( const JID& jid )
{
	printf( "updated %s\n", jid.bare().c_str() );
}

void ChatRoster::handleRoster( const Roster& roster )
{
	qDebug() << "Handle Roster";
	Roster::const_iterator it = roster.begin();
	for( ; it != roster.end(); ++it )
	{	
		JID roster_jid((*it).second->jid());
		QString contact = QString::fromStdString( (*it).second->name() );
		QString itemName;
		qDebug() << "Contact:" << contact;
		if (contact == QString(""))
		{
			itemName = QString::fromStdString(roster_jid.username());
		}
		else
		{
			itemName = contact;
		}
		
		qDebug() << "add contact jid: " << QString::fromStdString(roster_jid.full());
				
		ChatContactItemData *newContact = new ChatContactItemData(itemName, QString::fromStdString(roster_jid.full()));
		newContact->conn = conn;
		newContact->chatSess = newSession( roster_jid.full() );
		tree->NewChatWindow(newContact);
		tree->AddContact(newContact);
		//newContact->group = newContact->parent();
	}
}

void ChatRoster::handleRosterError( const IQ& iq )
{
	printf( "a roster-related error occured\n" );
}

void ChatRoster::handleRosterPresence( const RosterItem& item, const std::string& resource,
                          Presence::PresenceType presence, const std::string& /*msg*/ )
{
	printf( "presence received: %s/%s -- %d\n", item.jid().c_str(), resource.c_str(), presence );
}

void ChatRoster::handleSelfPresence( const RosterItem& item, const std::string& resource,
                          Presence::PresenceType presence, const std::string& /*msg*/ )
{
	printf( "self presence received: %s/%s -- %d\n", item.jid().c_str(), resource.c_str(), presence );
}

bool ChatRoster::handleSubscriptionRequest( const JID& jid, const std::string& /*msg*/ )
{
	qDebug() << "subscription: " << QString::fromStdString(jid.bare());
	StringList groups;
	JID id( jid );
	conn->rosterManager()->subscribe( id, "", groups, "" );
	return true;
}

bool ChatRoster::handleUnsubscriptionRequest( const JID& jid, const std::string& /*msg*/ )
{
	qDebug() << "unsubscription: " << QString::fromStdString(jid.bare());
	return true;
}

void ChatRoster::handleNonrosterPresence( const Presence &presence )
{
	printf( "received presence from entity not in the roster: %s\n", presence.from().full().c_str() );
	//StringList groups;
	//j->rosterManager()->subscribe( stanza->from(), "", groups, "" );
}

void ChatRoster::handleMessageSession( MessageSession *msgSes )
{
	qDebug() << "ChatMsgSess handleMessageSession";

	// this example can handle only one session. so we get rid of the old session
	if (m_session)
		conn->disposeMessageSession( m_session );
	m_session = msgSes;
	m_session->registerMessageHandler( this );
	
	// the following is optional
	//m_messageEventFilter = new MessageEventFilter( m_session );
	//m_messageEventFilter->registerMessageEventHandler( this );
	//m_chatStateFilter = new ChatStateFilter( m_session );
	//m_chatStateFilter->registerChatStateHandler( this );

}

void ChatRoster::handleMessage( const Message &msg, MessageSession *msgSes )
{
	QString from = QString::fromStdString(msgSes->target().username());
	QString text = QString::fromStdString(msg.body());
	qDebug() << "handle incomming Messages:" << from ;//<< "; has Win?: "<< contact->hasWin;
	for each (QTreeWidgetItem *i in tree->root->takeChildren())
	{
		ChatContactItemData *contact = (ChatContactItemData*)i;
		if(contact->jid.username() == msgSes->target().username())
		{
			tree->root->addChild(i);
			if (contact->hasWin)
			{
				contact->win->show();
				contact->win->chatText->append(from + ": " + text);
			}
			else
			{
				qDebug() << "For some reason this contact has no window!";
			}
		}
		else
		{
			tree->root->addChild(i);
		}
	}
}

MessageSession* ChatRoster::newSession( const JID& to )
{
	qDebug() << "newSession";
	MessageSession* session = new MessageSession( conn, to );
	session->registerMessageHandler( this );
	return session;
}
