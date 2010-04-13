#ifndef __TORRENT_MANAGER_H
#define __TORRENT_MANAGER_H
#include <QtGui>

	#include <libtorrent/config.hpp>
	#include <libtorrent/version.hpp>
	#include <libtorrent/session.hpp>
	#include <libtorrent/entry.hpp>
	#include <libtorrent/bencode.hpp>
	#include <libtorrent/identify_client.hpp>
	#include <libtorrent/alert_types.hpp>
	#include <libtorrent/ip_filter.hpp>
	#include <libtorrent/extensions/metadata_transfer.hpp>
	#include <libtorrent/extensions/ut_pex.hpp>
	#include <libtorrent/extensions/ut_metadata.hpp>
	/*
		construct a session
		parse torrent files and add to session; or add torrent hashs to session
		main loop:
			query the torrent_handles for progress (see torrent_handle)
			query the session for information
			add and remove torrents from the session at run-time
		save resume data
		destruct session object

	*/
	class TorrentAlertTimer;
	class DDPSConfig;
	class TransferManager;
	class TorrentTransferManager
	{
		public:
			TransferManager *tree;
			libtorrent::session se;
			libtorrent::session_settings settings;
			libtorrent::session_status status;
			TorrentAlertTimer *alert_timer;
			DDPSConfig *torrent_cfg;
			TorrentTransferManager(TransferManager *t);
			~TorrentTransferManager();

			libtorrent::torrent_handle AddTorrentFile(char const* file);
			libtorrent::torrent_handle AddTorrentHash(char const* name, 
				char const* tracker, std::string hash);

			void update_item_tree();

			bool startTransfer();
			bool cancelTransfer();
			bool pauseTransfer();
			bool finishTransfer();
			bool connectToPeers();
			bool downloadTorrent();
			bool uploadTorrent();
			bool setTransferSpeed();
			int getSessionStatus();
			
			libtorrent::dht_settings dht_settings;
			libtorrent::entry dht_state;
	};
	
/*	class TorrentTransfer : public TorrentTransferManager, public entry
	{
		public:
			int transferID;
			int progress;
			torrent_info torrentInfo;
			torrent_handle torrentHandle;
			//File fileList;
						
			TorrentTransfer(big_number const& hash);
			~TorrentTransfer();
			
			int getTransferAttributes();
			int getTransferProgress();			
			bool verifyFiles();
	}; */

#endif
