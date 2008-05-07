#include "TorrentManager.h"

TorrentTransferManager::TorrentTransferManager()
{
	torrentSessionSettings.user_agent = "DigitalDistributionPublishingSystem/" LIBTORRENT_VERSION;
	torrentSessionSettings.use_dht_as_fallback = false;
	
	session torrentSession;	
	
	torrentSession.start_upnp();
	torrentSession.start_natpmp();
	torrentSession.start_lsd();
	
	torrentSession.add_extension(&create_metadata_plugin);
	torrentSession.add_extension(&create_ut_pex_plugin);
	
	/*ses.set_max_uploads(upload_slots_limit);
	ses.set_max_half_open_connections(half_open_limit);
	ses.set_download_rate_limit(download_limit);
	ses.set_upload_rate_limit(upload_limit); */
	
	torrentSession.listen_on(std::make_pair(6881, 6889));
	torrentSession.set_settings(torrentSessionSettings);
	
	torrentSession.add_dht_router(std::make_pair(std::string("router.bittorrent.com"), 6881));
	torrentSession.add_dht_router(std::make_pair(std::string("router.utorrent.com"), 6881));
	torrentSession.add_dht_router(std::make_pair(std::string("router.bitcomet.com"), 6881));
	
	torrentSessionStatus = torrentSession.status();
}

TorrentTransferManager::~TorrentTransferManager()
{
	torrentSession.stop_lsd();
	torrentSession.stop_natpmp();
	torrentSession.stop_upnp();
	
	torrentSession.~session();
}

torrent_handle TorrentTransferManager::AddTorrent(big_number const& hash)
{	torrent_info tInfo = torrent_info(hash);
	torrent_handle h = torrentSession.add_torrent(tInfo, "./torrent-downloads");	
	handles.insert(std::make_pair(std::string(), h));
	h.set_max_connections(60);
	h.set_max_uploads(-1);
	h.set_ratio(2.0f);
	return h;
}