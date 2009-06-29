#include <client.h>
#include <presencehandler.h>
#include <presence.h>
#include <connectionlistener.h>
#include <connectiontcpclient.h>
#include <disco.h>
#include <gloox.h>
#include "ChatConnection.h"

ChatConn::ChatConn()
{
	//std::string username = myApp.LoginUsername.toStdString();
	//std::string password = myApp.LoginPassword.toStdString();
	std::string username = "testuser";
	std::string password = "testuser";

//#ifdef CHAT_SERVER
//	JID jid( username+"@"+ CHAT_SERVER +"/DDPSChat" );
//#else
	JID jid( username+"@localhost/DDPSChat" );
//#endif
	conn = new Client(jid, password);

	conn->setSASLMechanisms(SaslMechPlain);

	conn->registerConnectionListener( this );
	conn->registerPresenceHandler( this );

	conn->disco()->setVersion( "ddps", "client", "test" );
	conn->disco()->setIdentity( "client", "bot" );
	//conn->disco()->addFeature( XMLNS_CHAT_STATES );
	
	conn->setPresence( Presence::Available, 1 );
	
}

void ChatConn::onConnect()
{
	qDebug() << "connection";
}

void ChatConn::onDisconnect(ConnectionError e)
{
	qDebug() << "disconnection";
}

bool ChatConn::onTLSConnect(const CertInfo& info)
{
	qDebug() << "TLS Connection";
    return true;
}
