#include <QtGui>
#include "TransferTimer.h"
#include "TransferManager.h"

TransferManager::TransferManager(QWidget *parent) : QTreeWidget(parent)
{
	QStringList col_labels;
		col_labels << "Name" << "Size" << "Progress" << "Status" << "Down Speed" 
		<< "Up Speed" << "Downloaded" << "Uploaded" << "Peers" << "Seeds" << "Copies" << "metadata?";
	setColumnCount(col_labels.count());
	setHeaderLabels(col_labels);

	timer = new TransferManagerTimer(this, this);

	createItemRoots();

	timer->start();
}

TransferManager::~TransferManager()
{
	timer->stop();
}

void TransferManager::createItemRoots()
{
	games = new QTreeWidgetItem(this, QStringList("Games"));
	games_installed = new QTreeWidgetItem(games, QStringList("Installed"));
	games_ninstalled = new QTreeWidgetItem(games, QStringList("Not Installed"));

	media = new QTreeWidgetItem(this, QStringList("Media"));
	media_installed = new QTreeWidgetItem(media, QStringList("Installed"));
	media_ninstalled = new QTreeWidgetItem(media, QStringList("Not Installed"));

	tools = new QTreeWidgetItem(this, QStringList("Tools"));
	tools_installed = new QTreeWidgetItem(tools, QStringList("Installed"));
	tools_ninstalled = new QTreeWidgetItem(tools, QStringList("Not Installed"));

	add_item(media_installed, QStringList()<< "Media Test 1" << "str1");
	add_item(media_installed, QStringList("Media Test 2"));
	add_item(media_ninstalled, QStringList("Media Test 3"));
	add_item(media_ninstalled, QStringList("Media Test 4"));
}

void TransferManager::add_item(QTreeWidgetItem *item, QStringList &list )
{
	QTreeWidgetItem *newItem = new QTreeWidgetItem(list);
	item->addChild(newItem);
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
	connect(property_item, SIGNAL(triggered()), this, SLOT(OnMenuAddTorrent()));

	ItemMenu->exec(this->mapToGlobal(iPostion));
}

void TransferManager::contextMenuEvent(QContextMenuEvent *event)
{
	QTreeWidgetItem *item = 0;

	item = this->itemAt(event->pos());

	if(0 == item)
	{
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
}

void TransferManager::OnMenuStopItem()
{
}

void TransferManager::OnMenuPauseItem()
{
}

void TransferManager::OnMenuUpdateItem()
{
}

void TransferManager::OnMenuRemoveItem()
{
}

void TransferManager::OnMenuAddTorrent()
{
}

void TransferManager::OnMenuAddHttpDownload()
{
}

void TransferManager::OnMenuTorrentProperties()
{
}
