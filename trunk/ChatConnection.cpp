#include "ChatCommon.h"
#include "ChatConnection.h"

ChatConn::ChatConn()
{
	JID jid( "ddps@localhost/DDPSChat" );

	conn = new Client(jid, "letmein");

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
