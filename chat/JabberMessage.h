#ifndef __CHAT_MESSAGE_H
#define __CHAT_MESSAGE_H
	#include <QtGui>
	using namespace gloox;
	class ChatContactItemData;
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

#endif
