#include <QtGui>

#include "HttpManager.h"
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

TorrentDataItem::TorrentDataItem(libtorrent::torrent_handle h)
:QTreeWidgetItem(QStringList() << QString::fromStdString(h.name()), QTreeWidgetItem::UserType+1)
{
	handle = h;
	is_torrent = true;
	name = QString::fromStdString(h.name());
	QTimer *timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(update_item()));
	handle.resume();
	timer->start(500);
}

void TorrentDataItem::update_item()
{
	QString qStatus;

	if ( handle.is_valid() && !handle.is_paused() )
	{
		libtorrent::torrent_info ti = handle.get_torrent_info();
		libtorrent::torrent_status ts = handle.status();
		

		setData(0, Qt::DisplayRole, QString::fromStdString(ti.name()) );
		setData(1, Qt::DisplayRole, ti.total_size());
		setData(2, Qt::DisplayRole, (float)ts.progress);

		switch( ts.state )
		{
		case libtorrent::torrent_status::state_t::allocating:
			qStatus = QString("Allocating");
			break;
		case libtorrent::torrent_status::state_t::checking_files:
		case libtorrent::torrent_status::state_t::checking_resume_data:
		case libtorrent::torrent_status::state_t::queued_for_checking:
			qStatus = QString("Checking Files...");
			break;
		case libtorrent::torrent_status::state_t::downloading:
			qStatus = QString("Downloading");
			break;
		case libtorrent::torrent_status::state_t::downloading_metadata:
			qStatus = QString("Downloading Metadata");
			break;
		case libtorrent::torrent_status::state_t::finished:
			qStatus = QString("Finished");
			break;
		case libtorrent::torrent_status::state_t::seeding:
			qStatus = QString("Seeding");
			break;
		default:
			if (handle.is_paused()) qStatus = QString("Paused");
			else qStatus = QString("Unknown");
		}
		setText(3, qStatus);

		setData(4, Qt::DisplayRole, (float)ts.download_payload_rate);
		setData(5, Qt::DisplayRole, (float)ts.upload_payload_rate);
		setData(6, Qt::DisplayRole, ts.total_payload_download);
		setData(7, Qt::DisplayRole, ts.total_payload_upload);
		setData(8, Qt::DisplayRole, (int)ts.num_peers);
		setData(9, Qt::DisplayRole, (int)ts.num_seeds);
		setData(10, Qt::DisplayRole, (int)ts.num_complete);
	}
}

void TorrentDataItem::set_metadata()
{
	// metadata data
	//setData(11, Qt::DisplayRole, handle.get_torrent_info().metadata());

	// metadata hash, ie torrent hash
	//setData(11, Qt::DisplayRole, handle.get_torrent_info().info_hash);
}
