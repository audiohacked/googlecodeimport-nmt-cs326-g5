#ifndef __TORRENT_TIMER_H
#define __TORRENT_TIMER_H

	#include <wx/wxprec.h>

	#ifndef WX_PRECOMP
		#include <wx/wx.h>
	#endif

	#include <wx/utils.h>
	#include <wx/timer.h>
	
	#include "TorrentCommon.h"

	#include <libtorrent/config.hpp>
	#include <libtorrent/entry.hpp>
	#include <libtorrent/session.hpp>
	
	class TorrentManagerTimer : public wxTimer
	{
		public:
			TorrentManagerTimer(libtorrent::session &s, handles_t &list_hTorrent);
			void Notify();
			void start();
			handles_t *hTorList;
			libtorrent::session *ses;
			wxArrayString state_str;
			int active_torrent;
	};

#endif
