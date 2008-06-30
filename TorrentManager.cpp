#include "common.h"
#include "TorrentManager.h"
#include "TorrentBencode.h"

#include <libtorrent/extensions/metadata_transfer.hpp>
//#include <libtorrent/extensions/ut_pex.hpp>
#include <libtorrent/extensions/ut_metadata.hpp>

TorrentTransferManager::TorrentTransferManager(download_handles_t *l)
{
	handles = l;
	try
	{
		byte_kilo = 1000;
		listen_port = 6881;
		preferred_ratio = 0;
		download_limit = 200*byte_kilo;
		upload_limit = 190*byte_kilo;
		torrent_upload_limit = upload_limit;
		torrent_download_limit = download_limit;
		upload_slots_limit = 5;
		half_open_limit = -1;
		save_path_str = "./download-files";
		log_level = "info";
		ip_filter_file = "";
		allocation_mode = "full";
		bind_to_interface = "";
		proxy = "";
		proxy_login = "";
		proxy_type = "socks5";
		poll_interval = 2;
		wait_retry = 30;
		bind_port_start = 0;
		bind_port_end = 0;
	} catch(std::exception&) {}
	
	settings.user_agent = "DDPS/" LIBTORRENT_VERSION;
	settings.urlseed_wait_retry = wait_retry;
#if ((LIBTORRENT_VERSION_MINOR > 13) && (LIBTORRENT_VERSION_MAJOR >= 0))
	settings.outgoing_ports.first = bind_port_start;
	settings.outgoing_ports.second = bind_port_end;
#endif
	settings.use_dht_as_fallback = true;
	
	se.start_upnp();
	se.start_natpmp();
	se.start_lsd();
	
	//se.add_extension(&libtorrent::create_ut_pex_plugin);
	se.add_extension(&libtorrent::create_metadata_plugin);
	se.add_extension(&libtorrent::create_ut_metadata_plugin);

	se.set_max_uploads(upload_slots_limit);
	se.set_max_half_open_connections(half_open_limit);
	se.set_download_rate_limit(download_limit);
	se.set_upload_rate_limit(upload_limit);
	
	se.listen_on(std::make_pair(listen_port, listen_port+10));
	se.set_settings(settings);
	
	se.set_severity_level(libtorrent::alert::debug);

#if ((LIBTORRENT_VERSION_MINOR > 13) && (LIBTORRENT_VERSION_MAJOR >= 0))
	wxFile ses_state_file_handle(wxT(".ses_state"));
	if( ses_state_file_handle.IsOpened() )
	{
		wxFileInputStream ses_state_file(ses_state_file_handle);
		if(ses_state_file.IsOk())
		{
			libtorrent::entry ses_state;
			wxDataInputStream ses_state_data(ses_state_file);
			wx_bdecode(ses_state_file, ses_state_data, ses_state, 0);
			se.load_state(ses_state);
		}
	}
#endif

/*
	wxFile dht_state_file_handle(wxT(".dht_state"));
	if( dht_state_file_handle.IsOpened() )
	{
		wxFileInputStream dht_state_file(ses_state_file_handle);
		if(dht_state_file.IsOk())
		{
			wxDataInputStream dht_state_data(dht_state_file);
			wx_bdecode(dht_state_file, dht_state_data, dht_state, 0);
		}
	}
	else
	{
		//dht_state = libtorrent::entry();
	}
	
	dht_settings.max_peers_reply=20;
	dht_settings.search_branching=5;
	dht_settings.service_port=listen_port;
	dht_settings.max_fail_count=3;

	se.set_dht_settings(dht_settings);
	se.start_dht(dht_state);

	//se.add_dht_router(std::make_pair(std::string("router.bittorrent.com"), 6881));
	//se.add_dht_router(std::make_pair(std::string("router.utorrent.com"), 6881));
	//se.add_dht_router(std::make_pair(std::string("router.bitcomet.com"), 6881));
*/

	status = se.status();
}

TorrentTransferManager::~TorrentTransferManager()
{
	se.stop_dht();
	
#if ((LIBTORRENT_VERSION_MINOR > 13) && (LIBTORRENT_VERSION_MAJOR >= 0))
	libtorrent::entry session_state_out = se.state();
	wxFileOutputStream ses_state_file_out(wxT(".ses_state"));
	wxDataOutputStream ses_state_file_data(ses_state_file_out);
	wxTextOutputStream ses_state_file_text(ses_state_file_out);
	wx_bencode(ses_state_file_data, ses_state_file_text, session_state_out);
#endif

	libtorrent::entry dht_state_out = se.dht_state();
	wxFileOutputStream dht_state_file_out(wxT(".dht_state"));
	wxDataOutputStream dht_state_file_data(dht_state_file_out);
	wxTextOutputStream dht_state_file_text(dht_state_file_out);
	wx_bencode(dht_state_file_data, dht_state_file_text, dht_state_out);

	se.stop_lsd();
	se.stop_natpmp();
	se.stop_upnp();
}

libtorrent::torrent_handle TorrentTransferManager::AddTorrent(char const* name,
	char const* tracker, libtorrent::sha1_hash const& hash, long index)
{
	boost::filesystem::path save_path("./download_files/");

#if ((LIBTORRENT_VERSION_MINOR > 13) && (LIBTORRENT_VERSION_MAJOR >= 0))
	libtorrent::add_torrent_params p;
	p.name = name;
	p.save_path = "./download-files/";
	p.info_hash = hash;
	p.tracker_url = tracker;
	p.storage_mode = libtorrent::storage_mode_allocate;
	p.paused = false;
	p.duplicate_is_error = false;
	p.auto_managed = false;
	libtorrent::torrent_handle h = se.add_torrent(p);
#else
	libtorrent::torrent_handle h = se.add_torrent(tracker, hash, name, save_path);
#endif
	
	h.set_max_connections(10);
	h.set_max_uploads(-1);
	h.set_ratio(2.0f);
	h.set_upload_limit(torrent_upload_limit);
	h.set_download_limit(torrent_download_limit);
	h.resume();

	download_list::torrent_list_type torData;
	/*torData.dlg = new wxProgressDialog(wxString::FromAscii(name), 
		wxString::FromAscii(tracker), 100, ::wxGetApp().frame, 
		wxPD_CAN_ABORT | wxPD_APP_MODAL | wxPD_ELAPSED_TIME
		| wxPD_ESTIMATED_TIME | wxPD_REMAINING_TIME);*/
	torData.handle = h;

	
	handles->insert(std::make_pair(index, torData));
	
	return h;
}