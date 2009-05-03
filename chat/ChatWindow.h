#ifndef __CHAT_WINDOW_H
#define __CHAT_WINDOW_H

	#include <QtGui>
		
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
	
	class ChatContactItemData;
	class ChatWindowChat : public QDialog
	{
		public:
			ChatWindowChat(ChatContactItemData *id,QWidget *parent = 0);
			virtual ~ChatWindowChat();
			ChatContactItemData *contact_id;
			Client *m_client;
			QTextEdit *chatText;
			QLineEdit *sendText;
			QPushButton *sendButton;
		public slots:
			virtual void reject();
			void SendMsg();
			void TextChanged(const QString &text);
			void CreateWin();
		private:
			Q_OBJECT
	};
	
/*	
	class ChatWindowGroupChat : public QWidget
	{
		public:
			ChatWindowGroupChat(){}
			
	};
*/
#endif
