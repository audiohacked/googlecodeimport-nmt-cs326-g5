#include <QtGui>
#include "ChatBackend.h"
#include "ChatWindow.h"
#include "ChatRosterData.h"
#include "ChatRoster.h"
ChatWindowRoster::ChatWindowRoster(QWidget *parent)
:QDialog(parent)
{
	tree = new ChatRosterTree;
	force_disconnect = false;

	QVBoxLayout *mLayout = new QVBoxLayout;
	QWidget *userPanel = new QWidget(this);
	QWidget *optionsPanel = new QWidget(this);

	mLayout->addWidget(userPanel);
	mLayout->addWidget(tree);
	mLayout->addWidget(optionsPanel);

	setLayout(mLayout);

}

ChatWindowRoster::~ChatWindowRoster()
{
	force_disconnect = true;
	ChatDisconnect();
}

void ChatWindowRoster::ChatConnect()
{
	qDebug() << "try to connect to chat";
	if (!tree->roster->chat_connected)
		tree->roster->exec();
}

void ChatWindowRoster::ChatDisconnect()
{
	qDebug() << "disconnect chat";
	if (tree->roster->chat_connected || force_disconnect)
	{
		tree->roster->stop();
		tree->root->takeChildren();
	}
}

void ChatWindowRoster::accept(){done(QDialog::Accepted);}
void ChatWindowRoster::reject()
{	
	qDebug() << "close ChatWindowRoster??";
	hide();
	done(QDialog::Rejected);
}

ChatRosterTree::ChatRosterTree(QWidget *parent)
{
	QStringList col_labels;
		col_labels << "Screen Name";
	setColumnCount(1);
	setHeaderLabels(col_labels);
	root = new QTreeWidgetItem(this, QStringList() << "Friends");
	connect(this, SIGNAL(itemDoubleClicked(QTreeWidgetItem *, int)), this, SLOT(ContactItemDblClicked(QTreeWidgetItem *, int)));

	roster = new ChatRoster(this);
}

void ChatRosterTree::contextMenuEvent(QContextMenuEvent *event)
{
	QTreeWidgetItem *item = 0;

	item = this->itemAt(event->pos());

	if(0 == item)
	{
		QMenu *contextMenu = new QMenu(this);
		
		QAction *add_contact = new QAction(tr("Add Contact"), this);
		contextMenu->addAction(add_contact);
		connect(add_contact, SIGNAL(triggered()), this, SLOT(OnMenuAddContact()));

		QAction *connect_chat = new QAction(tr("Connect"), this);
		contextMenu->addAction(connect_chat);
		connect(connect_chat, SIGNAL(triggered()), (ChatWindowRoster*)parentWidget(), SLOT(ChatConnect()));

		QAction *disconnect_chat = new QAction(tr("Disconnect"), this);
		contextMenu->addAction(disconnect_chat);
		connect(disconnect_chat, SIGNAL(triggered()), (ChatWindowRoster*)parentWidget(), SLOT(ChatDisconnect()));

		contextMenu->exec(this->mapToGlobal(event->pos()));
	}
	else
	{
		ContactItemClicked(item, event->pos());
	}
}

void ChatRosterTree::ContactItemClicked(QTreeWidgetItem *item, const QPoint &iPostion)
{
	m_SelectedItem = item;

	QMenu *ItemMenu = new QMenu(this);
	
	QAction *remove_item = new QAction(tr("Remove Item"), this);
	ItemMenu->addAction(remove_item);
	connect(remove_item, SIGNAL(triggered()), this, SLOT(OnMenuRemoveContact()));
	
	ItemMenu->exec(this->mapToGlobal(iPostion));
}

void ChatRosterTree::ContactItemDblClicked(QTreeWidgetItem *item, int column)
{
	ChatContactItemData *contact = (ChatContactItemData *)item;
	if (item->parent() != NULL)
	{
		qDebug() << "ContactItem DblClicked";
		if (contact->hasWin)
		{
			contact->win->show();
		}
	}
}

void ChatRosterTree::OnMenuAddContact()
{
	AddContact(QString("Test user"), QString("testuser2@localhost/testing"));
}

void ChatRosterTree::OnMenuRemoveContact()
{
	if (m_SelectedItem->parent() != NULL)
	{
		ChatContactItemData *contact = (ChatContactItemData*)m_SelectedItem;
		qDebug() << "Remove Contact:" << contact->name << contact->qt_jid;
		root->removeChild(m_SelectedItem);
	}
}

void ChatRosterTree::AddContact(QString contact, QString jid)
{	
	ChatContactItemData *newContact = new ChatContactItemData(contact, jid);
	qDebug() << "Add Contact:" << newContact->name << newContact->qt_jid;
	NewChatWindow(newContact);
	root->addChild(newContact);
}

void ChatRosterTree::AddContact(ChatContactItemData *newContact)
{	
	qDebug() << "Add Contact:" << newContact->name << newContact->qt_jid;
	NewChatWindow(newContact);
	root->addChild(newContact);
}

void ChatRosterTree::NewChatWindow(ChatContactItemData *c)
{
	c->win = new ChatWindowChat(c, this);
}
