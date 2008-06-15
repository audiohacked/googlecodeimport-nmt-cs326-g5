#ifndef __CHAT_MESSAGE_H
#define __CHAT_MESSAGE_H

	#include <client.h>
	#include <message.h>
	#include <messagehandler.h>
	#include <messagesessionhandler.h>
	#include <messageeventhandler.h>
	#include <messageeventfilter.h>
	#include <chatstatehandler.h>
	#include <chatstatefilter.h>
	#include <gloox.h>
	using namespace gloox;

	class ChatMsgSess : public MessageSessionHandler, MessageEventHandler,
	 							ChatStateHandler, MessageHandler
	{
		public:
			ChatMsgSess(Client *conn);
			virtual void handleMessageSession( MessageSession *msgSes );
			virtual void handleMessage( const Message &msg, MessageSession *msgSes );
			virtual void handleMessageEvent(const JID &jid, MessageEventType MsgEvent);
			virtual void handleChatState( const JID &jid, ChatStateType ChatState);
			MessageSession *m_session;
			MessageEventFilter *m_messageEventFilter;
			ChatStateFilter *m_chatStateFilter;
			Client *m_client;

			MessageSession* ChatMsgSess::newSession( const JID& to );
	};

#endif
