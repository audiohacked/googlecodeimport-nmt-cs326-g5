#include "common.h"
#include "ChatCommon.h"
#include "ChatConnection.h"

ChatConn::ChatConn()
{
	DDPS &myApp = ::wxGetApp();
	std::string username = wx2glooxString(myApp.LoginUsername);
	std::string password = wx2glooxString(myApp.LoginPassword);
#ifdef CHAT_SERVER
	JID jid( username+"@"+ CHAT_SERVER +"/DDPSChat" );
#else
	JID jid( username+"@localhost/DDPSChat" );
#endif
	conn = new Client(jid, password);

	conn->setSASLMechanisms(SaslMechPlain);

	conn->registerConnectionListener( this );
	conn->registerPresenceHandler( this );

	conn->disco()->setVersion( "ddps", "client", "test" );
	conn->disco()->setIdentity( "client", "bot" );
	conn->disco()->addFeature( XMLNS_CHAT_STATES );
	
	conn->setPresence( Presence::Available, 1 );
	
}

void ChatConn::onConnect()
{
	wxLogMessage(wxT("connection"));
}

void ChatConn::onDisconnect(ConnectionError e)
{
	wxLogMessage(wxT("disconnection"));    
}

bool ChatConn::onTLSConnect(const CertInfo& info)
{
	wxLogMessage(wxT("TLS Connection"));
    return true;
}
