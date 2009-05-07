#include <QtGui>

#include "TorrentManager.h"
#include "TransferManagerData.h"
#include "TransferManager.h"
#include "TransferTimer.h"

TransferManagerTimer::TransferManagerTimer(TransferManager *listctrl, QObject *parent) : QTimer(parent)
{
	ctrl = listctrl;
	connect(this, SIGNAL(timeout()), this, SLOT(Notify()));
}

void TransferManagerTimer::Notify()
{
	//ctrl->tor->update_item_tree();
	ctrl->update();
}
