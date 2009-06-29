#ifndef __CHAT_ROSTER_H
#define __CHAT_ROSTER_H
	#include <QtGui>
	class ChatContactItemData;
	class ChatGroupItemData;
	class ChatRosterTree;
	class ChatRoster;
	class ChatWindowRoster : public QDialog
	{
		public:
			ChatWindowRoster(QWidget *parent=0);
			~ChatWindowRoster();
			ChatRosterTree *tree;
		public slots:
			virtual void accept();
			virtual void reject();
			void ChatConnect();
			void ChatDisconnect();
		private:
			bool force_disconnect;
			QMenu *roster_menu;
			Q_OBJECT
	};

	class ChatRosterTree : public QTreeWidget
	{
	public:
		ChatRosterTree(QWidget *parent=0);
		~ChatRosterTree(){}
		QTreeWidgetItem *root;
		ChatRoster *roster;
	public slots:
		void AddContact(QString contact, QString jid);
		void AddContact(ChatContactItemData *newContact);
		void NewChatWindow(ChatContactItemData *c);
	private slots:
		void ContactItemClicked(QTreeWidgetItem *item, const QPoint &iPostion);
		void ContactItemDblClicked(QTreeWidgetItem *item, int column);
		void OnMenuAddContact();
		void OnMenuRemoveContact();
	protected:
		virtual void contextMenuEvent(QContextMenuEvent *event);
	private:
		QTreeWidgetItem *m_SelectedItem;
		Q_OBJECT
	};
#endif
