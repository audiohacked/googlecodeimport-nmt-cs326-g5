#ifndef __TRANSFER_MANAGER_H
#define __TRANSFER_MANAGER_H
#include <QtGui>

class TransferManagerTimer;
class TorrentTransferManager;
class TorrentDataItem;
class HttpDataItem;
class HttpTransferManager;
class TransferUpdateViewThread;
class TransferManager : public QTreeWidget
{
	Q_OBJECT
	public:
		TransferManager(QWidget *parent = 0);
		~TransferManager();
		void add_item(QTreeWidgetItem *item, QStringList &list );
		void add_item_http(QTreeWidgetItem *item, const QUrl &url);
		void add_item_tor(QTreeWidgetItem *item, TorrentDataItem *tor );
		TorrentTransferManager *tor;
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
};
#endif
