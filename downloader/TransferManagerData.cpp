#include <QtGui>
#include "HttpManager.h"
#include "TransferManager.h"
#include "TransferManagerData.h"

HttpDataItem::HttpDataItem(HttpTransferManager *tm)
:QTreeWidgetItem(QStringList() << "http download", QTreeWidgetItem::UserType+2)
{
	handle = tm;
	name = QString("http download");//tm->http->dl_file->fileName();
	QTimer *timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(update_item()));
	timer->start(500);
}

void HttpDataItem::update_item()
{
	setText(0, handle->http->dl_file->fileName());
	setData(1, Qt::DisplayRole, (int)handle->http->dl_total);
	setData(2, Qt::DisplayRole, (float)handle->http->dl_progress);
	switch(handle->http->dl->state())
	{
	case QHttp::Unconnected:
		setText(3, QString("Unconnected"));
		break;
	case QHttp::HostLookup:
		setText(3, QString("HostLookup"));
		break;
	case QHttp::Connecting:
		setText(3, QString("Connecting"));
		break;
	case QHttp::Sending:
		setText(3, QString("Sending"));
		break;
	case QHttp::Reading:
		setText(3, QString("Downloading"));
		break;
	case QHttp::Connected:
		setText(3, QString("Connected"));
		break;
	case QHttp::Closing:
		setText(3, QString("Closing"));
		break;
	default:
		setText(3, QString("Unknown"));
	}
	setText(4, QString("Unknown"));
	setText(5, QString("Unknown"));
	setData(6, Qt::DisplayRole, (int)handle->http->dl_done);
	setText(7, QString("Unknown"));
	setText(8, QString("Unknown"));
	setText(9, QString("Unknown"));
	setText(10, QString("Unknown"));
}

