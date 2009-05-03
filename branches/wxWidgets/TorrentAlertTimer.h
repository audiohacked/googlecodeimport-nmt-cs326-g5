#ifndef __TORRENT_ALERT_TIMER_H
#define __TORRENT_ALERT_TIMER_H

	#include <wx/timer.h>
		
	class TorrentAlertTimer : public wxTimer
	{
		public:
			TorrentAlertTimer(libtorrent::session& s);
			void Notify();
			void start();
			void handle_alert(libtorrent::alert *a);
			libtorrent::session &session;
	};

#endif
