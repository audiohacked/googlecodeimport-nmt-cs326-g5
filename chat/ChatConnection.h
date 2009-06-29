#ifndef __CHAT_CONNECTION_H
#define __CHAT_CONNECTION_H
	#include <QtGui>

	using namespace gloox;
	class ChatConn : public ConnectionListener, PresenceHandler, QWidget
	{
		public:
			ChatConn();
			virtual void onConnect();
			virtual void onDisconnect( ConnectionError e );
			virtual bool onTLSConnect( const CertInfo& info );
			virtual void handlePresence( const Presence &presence )
			{
				conn->setPresence( Presence::Available, 1 );
			}
			
			Client *FetchConnection(){ return conn; }
			Client *conn;
	};

#endif
