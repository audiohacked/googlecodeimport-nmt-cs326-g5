#ifndef __CHAT_ROSTER_DATA_H
#define __CHAT_ROSTER_DATA_H

	#include <QtGui>
	
	#include <client.h>
	#include <gloox.h>
	using namespace gloox;

	class ChatMsgSess;
	class ChatWindowChat;

	class ChatContactItemData : public QTreeWidgetItem
	{
		public:
			ChatContactItemData(QString contact, QString contact_jid);
			virtual ~ChatContactItemData();
			Client *conn;
			MessageSession *chatSess;
			ChatWindowChat *win;
			QTreeWidgetItem *group;
			JID jid;
			QString name;
			QString qt_jid;
			bool hasWin;
	};

	class ChatGroupItemData : public QTreeWidgetItem
	{
		public:
			ChatGroupItemData(QString name, QTreeWidget *p = 0);
			void addChild(ChatContactItemData *child);
			QString name;
			QTreeWidget *parent;
			QTreeWidgetItem *me;
	};

#endif
