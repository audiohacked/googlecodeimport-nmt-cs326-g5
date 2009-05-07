#ifndef __TORRENT_ALERT_TIMER_H
#define __TORRENT_ALERT_TIMER_H

	#include <QtGui>

	#include <libtorrent/config.hpp>
	#include <libtorrent/entry.hpp>
	#include <libtorrent/bencode.hpp>
	#include <libtorrent/session.hpp>
	#include <libtorrent/alert_types.hpp>

	#include <boost/filesystem/operations.hpp>
	#include <boost/filesystem/fstream.hpp>

	class TorrentAlertTimer : public QTimer
	{
		Q_OBJECT
		public:
			TorrentAlertTimer(libtorrent::session& s);
			libtorrent::session &session;
			void handle_alert(libtorrent::alert *a);
		public slots:
			void Notify();
	};

#endif
