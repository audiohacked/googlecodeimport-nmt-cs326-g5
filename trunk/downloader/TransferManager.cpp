#include <QtGui>
#include "HttpManager.h"
#include "TransferTimer.h"
#include "TransferManagerData.h"
#include "TransferManagerDataTor.h"
#include "TransferManager.h"

TransferManager::TransferManager(QWidget *parent) : QTreeWidget(parent)
{
	QStringList col_labels;
		col_labels << "Name" << "Size" << "Progress" << "Status" << "Down Speed" 
		<< "Up Speed" << "Downloaded" << "Uploaded" << "Peers" << "Seeds" << "Copies";// << "metadata?";
	setColumnCount(col_labels.count());
	setHeaderLabels(col_labels);

	timer = new TransferManagerTimer(this, this);
#ifdef TORRENT_DOWNLOADER
	tor = new TorrentTransferManager(this);
#endif
	//http = new HttpTransferManager(this);

	createItemRoots();

	timer->start(500);
}

TransferManager::~TransferManager()
{
	timer->stop();
}

void TransferManager::createItemRoots()
{
	/*
	games = new QTreeWidgetItem(this, QStringList("Games"));
	games_installed = new QTreeWidgetItem(games, QStringList("Installed"));
	games_ninstalled = new QTreeWidgetItem(games, QStringList("Not Installed"));
	*/
	
	//media = new QTreeWidgetItem(this, QStringList("Media"));
	media_installed = new QTreeWidgetItem(this, QStringList("Installed"));
	media_ninstalled = new QTreeWidgetItem(this, QStringList("Not Installed"));

	/*
	tools = new QTreeWidgetItem(this, QStringList("Tools"));
	tools_installed = new QTreeWidgetItem(tools, QStringList("Installed"));
	tools_ninstalled = new QTreeWidgetItem(tools, QStringList("Not Installed"));
	*/

	/*
	add_item(media_installed, QStringList()<< "Media Test 1" << "str1");
	add_item(media_installed, QStringList("Media Test 2"));
	add_item(media_ninstalled, QStringList("Media Test 3"));
	add_item(media_ninstalled, QStringList("Media Test 4"));
	*/
}

void TransferManager::add_item(QTreeWidgetItem *item, QStringList &list )
{
	QTreeWidgetItem *newItem = new QTreeWidgetItem(list);
	item->addChild(newItem);
}

#ifdef TORRENT_DOWNLOADER
void TransferManager::add_item_tor(QTreeWidgetItem *item, TorrentDataItem *tor )
{
	item->addChild(tor);
}
#endif

void TransferManager::add_item_http(QTreeWidgetItem *item, const QUrl &url)
{
	HttpTransferManager *tm = new HttpTransferManager;
	HttpDataItem *i = new HttpDataItem(tm);
	item->addChild(i);
	tm->AddDownload(url);
}

void TransferManager::TransferItemClicked(QTreeWidgetItem *item, const QPoint &iPostion)
{
	m_SelectedItem = item;

	QMenu *ItemMenu = new QMenu(this);
	
	QAction *update_item = new QAction(tr("Update Item"), this);
	ItemMenu->addAction(update_item);
	connect(update_item, SIGNAL(triggered()), this, SLOT(OnMenuUpdateItem()));

	QAction *remove_item = new QAction(tr("Remove Item"), this);
	ItemMenu->addAction(remove_item);
	connect(remove_item, SIGNAL(triggered()), this, SLOT(OnMenuRemoveItem()));
	
	ItemMenu->addSeparator();

	QAction *start_item = new QAction(tr("Start Item"), this);
	ItemMenu->addAction(start_item);
	connect(start_item, SIGNAL(triggered()), this, SLOT(OnMenuStartItem()));

	QAction *stop_item = new QAction(tr("Stop Item"), this);
	ItemMenu->addAction(stop_item);
	connect(stop_item, SIGNAL(triggered()), this, SLOT(OnMenuStopItem()));

	QAction *pause_item = new QAction(tr("Pause Item"), this);
	ItemMenu->addAction(pause_item);
	connect(pause_item, SIGNAL(triggered()), this, SLOT(OnMenuPauseItem()));

	ItemMenu->addSeparator();

	QAction *property_item = new QAction(tr("Item Properties"), this);
	ItemMenu->addAction(property_item);
	connect(property_item, SIGNAL(triggered()), this, SLOT(OnMenuTorrentProperties()));

	ItemMenu->exec(this->mapToGlobal(iPostion));
}

void TransferManager::contextMenuEvent(QContextMenuEvent *event)
{
	QTreeWidgetItem *item = 0;

	item = this->itemAt(event->pos());

	if(0 == item)
	{
		return;
		QMenu *contextMenu = new QMenu(this);
		
		QAction *add_torrent = new QAction(tr("Add Torrent"), this);
		contextMenu->addAction(add_torrent);
		connect(add_torrent, SIGNAL(triggered()), this, SLOT(OnMenuAddTorrent()));

		QAction *add_httpdl = new QAction(tr("Add HTTP Download"), this);
		contextMenu->addAction(add_httpdl);
		connect(add_httpdl, SIGNAL(triggered()), this, SLOT(OnMenuAddHttpDownload()));

		contextMenu->exec(this->mapToGlobal(event->pos()));
	}
	else
	{
		TransferItemClicked(item, event->pos());
	}
}

void TransferManager::OnItemDeselected()
{
}

void TransferManager::OnItemSelected()
{
}

void TransferManager::OnMenuStartItem()
{
#ifdef TORRENT_DOWNLOADER
	if (m_SelectedItem->type() == (QTreeWidgetItem::UserType+1))
	{
		TorrentDataItem *tor = (TorrentDataItem*)m_SelectedItem;
		tor->handle.resume();
	}
	else if (m_SelectedItem->type() == (QTreeWidgetItem::UserType+2))
		return;
#else
	return;
#endif
}

void TransferManager::OnMenuStopItem()
{
#ifdef TORRENT_DOWNLOADER
	if (m_SelectedItem->type() == (QTreeWidgetItem::UserType+1))
	{
		TorrentDataItem *tor = (TorrentDataItem*)m_SelectedItem;
		tor->handle.pause();
	}
	else if (m_SelectedItem->type() == (QTreeWidgetItem::UserType+2))
		return;
#else
	return;
#endif
}

void TransferManager::OnMenuPauseItem()
{
#ifdef TORRENT_DOWNLOADER
	if (m_SelectedItem->type() == (QTreeWidgetItem::UserType+1))
	{
		TorrentDataItem *tor = (TorrentDataItem*)m_SelectedItem;
		tor->handle.pause();
	}
	else if (m_SelectedItem->type() == (QTreeWidgetItem::UserType+2))
		return;
#else
	return;
#endif
}

void TransferManager::OnMenuUpdateItem()
{
#ifdef TORRENT_DOWNLOADER
	if (m_SelectedItem->type() == (QTreeWidgetItem::UserType+1))
	{
		TorrentDataItem *i = (TorrentDataItem*)m_SelectedItem;
		i->update_item();
	}
	else if (m_SelectedItem->type() == (QTreeWidgetItem::UserType+2))
	{
		HttpDataItem *i = (HttpDataItem*)m_SelectedItem;
		i->update_item();
	}
#else
	HttpDataItem *i = (HttpDataItem*)m_SelectedItem;
	i->update_item();
#endif
}

void TransferManager::OnMenuRemoveItem()
{
#ifdef TORRENT_DOWNLOADER
	if (m_SelectedItem->type() == (QTreeWidgetItem::UserType+1))
	{
		TorrentDataItem *i = (TorrentDataItem*)m_SelectedItem;
		media_installed->removeChild(i);
	}
	else if (m_SelectedItem->type() == (QTreeWidgetItem::UserType+2))
		return;
#else
	return;
#endif
}

void TransferManager::OnMenuAddTorrent()
{
#ifdef TORRENT_DOWNLOADER
	//tor->AddTorrentHash("test", "http://torrent.ubuntu.com:6969/announce", "60d5d82328b4547511fdeac9bf4d0112daa0ce00");
	tor->AddTorrentFile("./test.torrent");
#endif
}

void TransferManager::OnMenuAddHttpDownload()
{
	HttpTransferManager *tm = new HttpTransferManager;
	HttpDataItem *i = new HttpDataItem(tm);
	media_installed->addChild(i);
	tm->AddDownload(QUrl( "http://mirrors.cat.pdx.edu/ubuntu-releases/jaunty/ubuntu-9.04-desktop-i386.iso" ));
}

void TransferManager::OnMenuTorrentProperties()
{
}
