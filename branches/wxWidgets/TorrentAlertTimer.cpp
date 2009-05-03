#include <wx/wxprec.h>

#ifndef WX_PRECOMP
	#include <wx/wx.h>
#endif

#include <wx/utils.h>
#include <wx/timer.h>

#include <libtorrent/config.hpp>
#include <libtorrent/entry.hpp>
#include <libtorrent/bencode.hpp>
#include <libtorrent/session.hpp>
#include <libtorrent/alert_types.hpp>

#include "TorrentAlertTimer.h"

TorrentAlertTimer::TorrentAlertTimer(libtorrent::session &s) : wxTimer(), session(s)
{
}

void TorrentAlertTimer::Notify()
{
	std::auto_ptr<libtorrent::alert> a;
	a = session.pop_alert();
	while (a.get())
	{
		if (a->category() & libtorrent::alert::error_notification)
		{
			//event_string << esc("31");
		}
		else if (a->category() & (libtorrent::alert::peer_notification | libtorrent::alert::storage_notification))
		{
			//event_string << esc("33");
		}
		wxLogDebug(wxString(a->message().c_str(), wxConvUTF8));
		handle_alert(a.get());
		a = session.pop_alert();
	}
}

void TorrentAlertTimer::start()
{
	wxTimer::Start(100);
}

void TorrentAlertTimer::handle_alert(libtorrent::alert *a)
{
	if (libtorrent::torrent_finished_alert* p = dynamic_cast<libtorrent::torrent_finished_alert*>(a))
	{
		p->handle.set_max_connections(30);

		// write resume data for the finished torrent
		libtorrent::torrent_handle h = p->handle;
		h.save_resume_data();
	}
	else if (libtorrent::save_resume_data_alert* p = dynamic_cast<libtorrent::save_resume_data_alert*>(a))
	{
		libtorrent::torrent_handle h = p->handle;
		//TORRENT_ASSERT(p->resume_data);
		if (p->resume_data)
		{
			boost::filesystem::ofstream out(h.save_path() / (h.name() + ".fastresume")
				, std::ios_base::binary);
			out.unsetf(std::ios_base::skipws);
			libtorrent::bencode(std::ostream_iterator<char>(out), *p->resume_data);
			if (h.is_paused() && !h.is_auto_managed()) session.remove_torrent(h);
		}
	}
}
