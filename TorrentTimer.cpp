#include "TorrentTimer.h"

TorrentManagerTimer::TorrentManagerTimer(libtorrent::session &s, handles_t &list_hTorrent) : wxTimer()
{
	hTorList = &list_hTorrent;
	ses = &s;
	active_torrent = 0;
	
	try
	{
		state_str.Add(wxString( 	wxT("checking queue") 	));
		state_str.Add(wxString( 	wxT("checking files") 	));
		state_str.Add(wxString( 	wxT("connecting") 		));
		state_str.Add(wxString( 	wxT("dl metadata") 		));
		state_str.Add(wxString( 	wxT("downloading") 		));
		state_str.Add(wxString( 	wxT("finished") 		));
		state_str.Add(wxString( 	wxT("seeding") 			));
		state_str.Add(wxString( 	wxT("allocating") 		)); 
	} catch(std::exception&) {}

	/*
		passed variables needed (maybe):
			torrent handles
			session handle
	*/
}

void TorrentManagerTimer::Notify()
{
	//wxLogMessage(wxT("TorrentManagerTimer - Notify"));
/*
	for each active torrent;do
		get torrent status
		update wxGauge with current downloaded bytes status
*/
	if(!hTorList->empty())
	{
		for (handles_t::iterator i = hTorList->begin(); i != hTorList->end(); ++i)
		{
			//wxLogMessage(wxT("TorrentManagerTimer - checking single torrent"));
			libtorrent::torrent_handle& h = i->second.handle;
			wxProgressDialog *d = i->second.dlg;
			if (h.is_valid())
			{
				bool keepGoing = true;
				bool skip = false;
				libtorrent::torrent_status s = h.status();
				keepGoing = d->Update(s.progress * 100, state_str.Item(s.state), &skip);
				if (!keepGoing)
				{	
					ses->remove_torrent(h);
					d->Destroy();
				}
			}
		}
	}
	else
	{
		//wxLogMessage(wxT("TorrentManagerTimer - empty torrent list"));
	}
}

void TorrentManagerTimer::start()
{
	wxTimer::Start(500);
}