#include "common.h"
#include "TorrentManager.h"
#include "TorrentBencode.h"

TorrentTransferManager::TorrentTransferManager()
{
	try
	{
		listen_port = 6881;
		preferred_ratio = 0;
		download_limit = 0;
		upload_limit = 0;
		torrent_upload_limit = 20;
		torrent_download_limit = 0;
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
	settings.outgoing_ports.first = bind_port_start;
	settings.outgoing_ports.second = bind_port_end;
	settings.use_dht_as_fallback = true;
	
	se.start_upnp();
	se.start_natpmp();
	se.start_lsd();
	
	se.add_extension(&create_metadata_plugin);
	//se.add_extension(&create_ut_metadata_plugin);
	//se.add_extension(&create_ut_pex_plugin);
	
	se.set_max_uploads(upload_slots_limit);
	se.set_max_half_open_connections(half_open_limit);
	se.set_download_rate_limit(download_limit);
	se.set_upload_rate_limit(upload_limit);
	
	se.listen_on(std::make_pair(listen_port, listen_port+10), bind_to_interface.c_str());
	se.set_settings(settings);
	
	se.set_severity_level(alert::debug);

	wxFile ses_state_file_handle(wxT(".ses_state"));
	if( ses_state_file_handle.IsOpened() )
	{
		wxFileInputStream ses_state_file(ses_state_file_handle);
		if(ses_state_file.IsOk())
		{
			entry ses_state;
			wxDataInputStream ses_state_data(ses_state_file);
			wx_bdecode(ses_state_file, ses_state_data, ses_state, 0);
			se.load_state(ses_state);
		}
	}
	
	wxFile dht_state_file_handle(wxT(".dht_state"));
	if( dht_state_file_handle.IsOpened() )
	{
		wxFileInputStream dht_state_file(ses_state_file_handle);
		if(dht_state_file.IsOk())
		{
			entry dht_state;
			wxDataInputStream dht_state_data(dht_state_file);
			wx_bdecode(dht_state_file, dht_state_data, dht_state, 0);
			se.start_dht(entry());
			se.add_dht_router(std::make_pair(std::string("router.bittorrent.com")
				, 6881));
			se.add_dht_router(std::make_pair(std::string("router.utorrent.com")
				, 6881));
			se.add_dht_router(std::make_pair(std::string("router.bitcomet.com")
				, 6881));
		}
	}

	status = se.status();
}

TorrentTransferManager::~TorrentTransferManager()
{
	entry session_state_out = se.state();
	wxFileOutputStream ses_state_file_out(wxT(".ses_state"));
	wxDataOutputStream ses_state_file_data(ses_state_file_out);
	wxTextOutputStream ses_state_file_text(ses_state_file_out);
	wx_bencode(ses_state_file_data, ses_state_file_text, session_state_out);

	entry dht_state_out = se.dht_state();
	wxFileOutputStream dht_state_file_out(wxT(".dht_state"));
	wxDataOutputStream dht_state_file_data(dht_state_file_out);
	wxTextOutputStream dht_state_file_text(dht_state_file_out);
	wx_bencode(dht_state_file_data, dht_state_file_text, dht_state_out);

	se.stop_lsd();
	se.stop_natpmp();
	se.stop_upnp();
}

torrent_handle TorrentTransferManager::AddTorrent(char const* name, char const* tracker, big_number const& hash)
{
	add_torrent_params p;
	p.name = name;
	p.save_path = "./download-files/";
	p.info_hash = hash;
	p.tracker_url = tracker;
	p.storage_mode = storage_mode_allocate;
	p.paused = true;
	p.duplicate_is_error = false;
	p.auto_managed = true;
	
	torrent_handle h = se.add_torrent(p);	

	handles.insert(std::make_pair(std::string(p.name), h));

	h.set_max_connections(60);
	h.set_max_uploads(-1);
	h.set_ratio(2.0f);
	h.set_upload_limit(torrent_upload_limit);
	h.set_download_limit(torrent_download_limit);
	h.resume();
	
	return h;
}