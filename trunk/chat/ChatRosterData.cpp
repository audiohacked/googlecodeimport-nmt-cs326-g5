#include <QtGui>
#include "ChatRosterData.h"

ChatContactItemData::ChatContactItemData(QString contact, QString contact_jid)
:QTreeWidgetItem(QStringList() << contact, QTreeWidgetItem::UserType)
{
	jid = JID(contact_jid.toStdString());
	qt_jid = contact_jid;
	name = contact;
	hasWin = false;
	win = NULL;
	//chatSess = new ChatMsgSess(this);

}

ChatContactItemData::~ChatContactItemData()
{
	hasWin = false;
}

ChatGroupItemData::ChatGroupItemData(QString n, QTreeWidget *p)
:QTreeWidgetItem(p, QTreeWidgetItem::UserType)
{
	name = n;
	parent = p;
	setData(0, Qt::DisplayRole, name);
	//QTreeWidgetItem(p, QTreeWidgetItem::UserType);
	//me = this;
}

void ChatGroupItemData::addChild(ChatContactItemData *child)
{
	//child->win = new ChatWindowChat(child);
	//child->hasWin = true;
	QTreeWidgetItem::addChild(child);
}