#ifndef __CHAT_CONNECTION_H
#define __CHAT_CONNECTION_H

	#include <wx/wxprec.h>
	#ifndef WX_PRECOMP
		#include <wx/wx.h>
	#endif

	//#include "ChatCommon.h"

	#include <client.h>
	
	#include <presencehandler.h>
	#include <presence.h>
	
	#include <connectionlistener.h>
	#include <connectiontcpclient.h>
	#include <disco.h>
	#include <gloox.h>
	using namespace gloox;

	class ChatConn : public ConnectionListener, PresenceHandler
	{
		public:
			ChatConn();
			virtual void onConnect();
			virtual void onDisconnect( ConnectionError e );
			virtual bool onTLSConnect( const CertInfo& info );
			virtual void handlePresence( const Presence &presence )
			{
				//conn->setPresence( Presence::Available, 1 );
			}
			
			Client *FetchConnection(){ return conn; }
			
		private:
			Client *conn;
	};

#endif
