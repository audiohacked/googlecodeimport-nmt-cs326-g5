#ifndef __TRANSFER_MANAGER_DATA_H
#define __TRANSFER_MANAGER_DATA_H

	#include <libtorrent/config.hpp>
	#include <libtorrent/version.hpp>
	#include <libtorrent/session.hpp>
	#include <libtorrent/entry.hpp>
	#include <libtorrent/bencode.hpp>
	#include <libtorrent/identify_client.hpp>
	#include <libtorrent/alert_types.hpp>
	#include <libtorrent/ip_filter.hpp>
#include <QtGui>

	class TorrentDataItem : public QObject, public QTreeWidgetItem
	{
	Q_OBJECT
	public:
		TorrentDataItem(libtorrent::torrent_handle h);
		libtorrent::torrent_handle handle;
		QString name;
		bool is_torrent;
	public slots:
		void update_item();
		void set_metadata();
	private:
	};
#endif
