#include <QtGui>
#include "TransferManager.h"
#include "TransferManagerDataTor.h"

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

		/*switch( ts.state )
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
		setText(3, qStatus);*/

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
