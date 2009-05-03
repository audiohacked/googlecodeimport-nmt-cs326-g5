#include <QtGui>

#include "TorrentManager.h"
//#include "TorrentBencode.h"

#include <libtorrent/config.hpp>
#include <libtorrent/version.hpp>

#include <libtorrent/session.hpp>
#include <libtorrent/entry.hpp>
#include <libtorrent/bencode.hpp>

#include <libtorrent/identify_client.hpp>
#include <libtorrent/alert_types.hpp>
#include <libtorrent/ip_filter.hpp>

#if ((LIBTORRENT_VERSION_MINOR > 13) && (LIBTORRENT_VERSION_MAJOR >= 0))
#include <libtorrent/magnet_uri.hpp>
#include <libtorrent/bitfield.hpp>
#endif

#include <string>

//#include "TorrentCommon.h"

#include <libtorrent/extensions/metadata_transfer.hpp>
#include <libtorrent/extensions/ut_pex.hpp>
#include <libtorrent/extensions/ut_metadata.hpp>

int byte_kilo = 1000;

TorrentTransferManager::TorrentTransferManager(download_handles_t *l)
{
	torrent_cfg = new DDPSConfig;
	handles = l;
	
	settings.user_agent = "DDPS/" LIBTORRENT_VERSION;
	settings.urlseed_wait_retry = torrent_cfg->cfg_wait_retry;
#if ((LIBTORRENT_VERSION_MINOR > 13) && (LIBTORRENT_VERSION_MAJOR >= 0))
	settings.outgoing_ports.first = torrent_cfg->cfg_bind_port_start;
	settings.outgoing_ports.second = torrent_cfg->cfg_bind_port_end;
#endif
	settings.use_dht_as_fallback = true;
	
	se.start_upnp();
	se.start_natpmp();
	se.start_lsd();
	
	se.add_extension(&libtorrent::create_ut_pex_plugin);
	se.add_extension(&libtorrent::create_metadata_plugin);
	se.add_extension(&libtorrent::create_ut_metadata_plugin);

	se.set_max_uploads(torrent_cfg->cfg_upload_slots_limit);
	se.set_max_half_open_connections(torrent_cfg->cfg_half_open_limit);
	se.set_download_rate_limit(torrent_cfg->cfg_download_speed*byte_kilo);
	se.set_upload_rate_limit(torrent_cfg->cfg_upload_speed*byte_kilo);
	
	se.listen_on(std::make_pair(torrent_cfg->cfg_listen_port, torrent_cfg->cfg_listen_port+10));
	se.set_settings(settings);
	
	//se.set_severity_level(libtorrent::alert::info);
	se.set_alert_mask(libtorrent::alert::all_categories);

#if ((LIBTORRENT_VERSION_MINOR > 13) && (LIBTORRENT_VERSION_MAJOR >= 0))
	QFile ses_state_file(tr(".ses_state"));
	ses_state_file.open(QIODevice::ReadOnly);
	if( ses_state_file.IsOpen() )
	{
		libtorrent::entry ses_state;
		bdecode(ses_state_file, ses_state, 0);
		se.load_state(ses_state);
	}
#endif


	dht_settings.max_peers_reply=torrent_cfg->cfg_max_peers;
	dht_settings.search_branching=5;
	dht_settings.service_port=torrent_cfg->cfg_listen_port;
	dht_settings.max_fail_count=3;
	se.set_dht_settings(dht_settings);

	QFile dht_state_file_handle(tr(".dht_state"));
	dht_state_file_handle.open(QIODevice::ReadOnly);
	if( dht_state_file_handle.IsOpen() )
	{
		bdecode(dht_state_file_handle, dht_state, 0);
		se.start_dht(dht_state);
	}
	else
	{
		se.start_dht();
	}

	se.add_dht_router(std::make_pair(std::string("router.bittorrent.com"), 6881));
	se.add_dht_router(std::make_pair(std::string("router.utorrent.com"), 6881));
	se.add_dht_router(std::make_pair(std::string("router.bitcomet.com"), 554));
	
	alert_timer = new TorrentAlertTimer(se);
	alert_timer->start();
}

TorrentTransferManager::~TorrentTransferManager()
{
	se.stop_dht();
	
#if ((LIBTORRENT_VERSION_MINOR > 13) && (LIBTORRENT_VERSION_MAJOR >= 0))
	libtorrent::entry session_state_out = se.state();
	QFile ses_state_file_out(wxT(".ses_state"));
	QDataStream ses_state_file_data(ses_state_file_out);
	bencode(ses_state_file_data, session_state_out);
#endif

	libtorrent::entry dht_state_out = se.dht_state();
	QFile dht_state_file_out(wxT(".dht_state"));
	QDataStream dht_state_file_data(dht_state_file_out);
	bencode(dht_state_file_data, dht_state_out);

	se.stop_lsd();
	se.stop_natpmp();
	se.stop_upnp();
}

libtorrent::torrent_handle
TorrentTransferManager::AddTorrentHash(char const* name,
	char const* tracker, libtorrent::sha1_hash const& hash, long index)
{
	boost::filesystem::path save_path(torrent_cfg->cfg_download_location.toStdString());

#if ((LIBTORRENT_VERSION_MINOR > 13) && (LIBTORRENT_VERSION_MAJOR >= 0))
	libtorrent::add_torrent_params p;
	p.name = name;
	p.save_path = save_path;
	p.info_hash = hash;
	p.tracker_url = tracker;
	p.storage_mode = libtorrent::storage_mode_allocate;
	p.paused = true;
	p.duplicate_is_error = false;
	p.auto_managed = false;
	libtorrent::torrent_handle h = se.add_torrent(p);
#else
	libtorrent::torrent_handle h = se.add_torrent(tracker, hash, name, save_path);
#endif
	
	h.set_max_connections(10);
	h.set_max_uploads(-1);
	h.set_ratio(2.0f);
	h.set_upload_limit(torrent_cfg->cfg_upload_speed*byte_kilo);
	h.set_download_limit(torrent_cfg->cfg_download_speed*byte_kilo);
	//h.resume();

	download_list::torrent_list_type torData;
	torData.handle = h;

	handles->insert(std::make_pair(index, torData));
	
	return h;
}

libtorrent::torrent_handle 
TorrentTransferManager::AddMagnetURI(char const* uri, long index)
{
	boost::filesystem::path save_path(torrent_cfg->cfg_download_location.toStdString());

	libtorrent::torrent_handle h = libtorrent::add_magnet_uri(se, uri,
		save_path, libtorrent::storage_mode_sparse);

	h.set_max_connections(10);
	h.set_max_uploads(-1);
	h.set_ratio(2.0f);
	h.set_upload_limit(torrent_cfg->cfg_upload_speed*byte_kilo);
	h.set_download_limit(torrent_cfg->cfg_download_speed*byte_kilo);

	download_list::torrent_list_type torData;
	torData.handle = h;

	handles->insert(std::make_pair(index, torData));

	return h;
}

libtorrent::torrent_handle 
TorrentTransferManager::AddTorrentFile(char const* file, long index)
{
	boost::filesystem::path save_path(torrent_cfg->cfg_download_location.toStdString());

	boost::intrusive_ptr<libtorrent::torrent_info> torrent_file_info(
		new libtorrent::torrent_info(file)
	);

	libtorrent::add_torrent_params p;
	p.ti = torrent_file_info;
	p.save_path = save_path;
	p.storage_mode = libtorrent::storage_mode_sparse;
	p.paused = true;
	p.duplicate_is_error = false;
	p.auto_managed = false;

	libtorrent::torrent_handle h = se.add_torrent(p);

	h.set_max_connections(10);
	h.set_max_uploads(-1);
	h.set_ratio(2.0f);
	h.set_upload_limit(torrent_cfg->cfg_upload_speed*byte_kilo);
	h.set_download_limit(torrent_cfg->cfg_download_speed*byte_kilo);

	download_list::torrent_list_type torData;
	torData.handle = h;

	handles->insert(std::make_pair(index, torData));

	//h.resume();
	return h;
}
