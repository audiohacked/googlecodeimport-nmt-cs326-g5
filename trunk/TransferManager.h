#ifndef __TRANSFER_MANAGER_H
#define __TRANSFER_MANAGER_H
	#include <QtGui>
	class TransferManagerTimer;
	class TransferManager : public QTreeWidget
	{
		public:
			TransferManager(QWidget *parent = 0);
			~TransferManager();
			void add_item(QTreeWidgetItem *item, QStringList &list );
			TransferManagerTimer *timer;
			QTreeWidgetItem *games_installed;
			QTreeWidgetItem *media_installed;
			QTreeWidgetItem *tools_installed;
			QTreeWidgetItem *games_ninstalled;
			QTreeWidgetItem *media_ninstalled;
			QTreeWidgetItem *tools_ninstalled;
		private slots:
			void TransferItemClicked(QTreeWidgetItem *item, const QPoint &iPostion);
			void OnItemDeselected();
			void OnItemSelected();
			void OnMenuStartItem();
			void OnMenuStopItem();
			void OnMenuPauseItem();
			void OnMenuUpdateItem();
			void OnMenuRemoveItem();
			void OnMenuAddTorrent();
			void OnMenuAddHttpDownload();
			void OnMenuTorrentProperties();
		protected:
			virtual void contextMenuEvent(QContextMenuEvent *event);
		private:
			void createItemRoots();
			QTreeWidgetItem *m_SelectedItem;
			QTreeWidgetItem *games;
			QTreeWidgetItem *media;
			QTreeWidgetItem *tools;
			Q_OBJECT
	};

#endif
