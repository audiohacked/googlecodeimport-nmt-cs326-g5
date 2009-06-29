#ifndef __CHAT_BACKEND_H
#define __CHAT_BACKEND_H
	#include <QtGui>
	#include <client.h>
	#include <rostermanager.h>
	#include <message.h>
	#include <messagehandler.h>
	#include <messagesessionhandler.h>
	#include <messageeventhandler.h>
	#include <messageeventfilter.h>
	#include <chatstatehandler.h>
	#include <chatstatefilter.h>
	#include <presencehandler.h>
	#include <presence.h>
	#include <connectionlistener.h>
	#include <connectiontcpclient.h>
	#include <disco.h>
	#include <gloox.h>
	using namespace gloox;
	class ChatRosterTree;
	class ChatConnThread;
	class ChatContactItemData;
	class DDPSConfig;
	class ChatRoster : public QObject, RosterListener, ConnectionListener, 
		PresenceHandler, MessageSessionHandler, MessageHandler
	{
	Q_OBJECT
	public:
		ChatRoster(ChatRosterTree *t2, QObject *parent = 0);
	    ~ChatRoster(){}
		void exec();
		void stop();

		virtual void onConnect();
		virtual void onDisconnect( ConnectionError e );
		virtual bool onTLSConnect( const CertInfo& info );
		
		virtual void handlePresence( const Presence &presence );

		virtual void handleItemSubscribed( const JID& jid );
		virtual void handleItemAdded( const JID& jid );
		virtual void handleItemUnsubscribed( const JID& jid );
		virtual void handleItemRemoved( const JID& jid );
		virtual void handleItemUpdated( const JID& jid );
		virtual void handleRoster( const Roster& roster );
		virtual void handleRosterError(  const IQ &iq  );
		virtual void handleRosterPresence( const RosterItem& item, 
			const std::string& resource, Presence::PresenceType presence,
			const std::string& msg );

	    virtual void handleSelfPresence( const RosterItem& item, 
			const std::string& resource, Presence::PresenceType presence,
			const std::string& msg );
		
		virtual bool handleSubscriptionRequest( const JID& jid, const std::string& msg );
		virtual bool handleUnsubscriptionRequest( const JID& jid, const std::string& msg );
		virtual void handleNonrosterPresence( const Presence &presence );
		
		virtual void handleMessageSession( MessageSession *msgSes );
		virtual void handleMessage( const Message &msg, MessageSession *msgSes );

	    Client *conn;
		bool chat_connected;
		MessageSession *m_session;
		MessageSession* newSession( const JID& to );

	public slots:
		virtual void processMessages();
	private:
		DDPSConfig *chat_cfg;
		QTimer *t;
		ChatRosterTree *tree;
	protected:
		virtual void onResourceBindError( ResourceBindError error );
		virtual void onSessionCreateError( SessionCreateError error );
	};
	

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

	/*
	class ChatMsgSess : public QObject, MessageSessionHandler, MessageHandler
	{
		public:
			ChatMsgSess(ChatContactItemData *c, QObject *parent = 0);
			virtual void handleMessageSession( MessageSession *msgSes );
			virtual void handleMessage( const Message &msg, MessageSession *msgSes );
			MessageSession *m_session;
			Client *m_client;
			ChatContactItemData *contact;
			MessageSession* newSession( const JID& to );
	};
	*/
#endif
