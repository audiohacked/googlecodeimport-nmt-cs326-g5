#ifndef __TORRENT_MANAGER_H
#define __TORRENT_MANAGER_H
	#include <wx/wxprec.h>

	#ifndef WX_PRECOMP
		#include <wx/wx.h>
	#endif

	#include <wx/progdlg.h>

	#include <boost/filesystem/operations.hpp>
	#include <boost/filesystem/convenience.hpp>
	#include <boost/filesystem/fstream.hpp>
	#include <boost/filesystem/exception.hpp>
	#include <boost/bind.hpp>
	#include <boost/program_options.hpp>
	#include <boost/regex.hpp>

	#include <libtorrent/config.hpp>
	#include <libtorrent/version.hpp>

	#include <libtorrent/entry.hpp>
	#include <libtorrent/bencode.hpp>
	#include <libtorrent/session.hpp>

	#include <libtorrent/identify_client.hpp>
	#include <libtorrent/alert_types.hpp>
	#include <libtorrent/ip_filter.hpp>

#if ((LIBTORRENT_VERSION_MINOR > 13) && (LIBTORRENT_VERSION_MAJOR >= 0))
	#include <libtorrent/magnet_uri.hpp>
	#include <libtorrent/bitfield.hpp>
#endif
	
	#include <string>
	
	#include "TorrentCommon.h"

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
	
	class TorrentTransferManager
	{
		public:
			libtorrent::session se;
			libtorrent::session_settings settings;
			libtorrent::session_status status;
			download_handles_t *handles;

			TorrentTransferManager(download_handles_t *l);
			~TorrentTransferManager();

			libtorrent::torrent_handle AddTorrent(char const* name, 
				char const* tracker, libtorrent::sha1_hash const& hash, long index);

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
			
			int byte_kilo;
			int listen_port;
			float preferred_ratio;
			int download_limit;
			int upload_limit;
			int torrent_upload_limit;
			int torrent_download_limit;
			int upload_slots_limit;
			int half_open_limit;
			std::string save_path_str;
			std::string log_level;
			std::string ip_filter_file;
			std::string allocation_mode;
			std::string bind_to_interface;
			std::string proxy;
			std::string proxy_login;
			std::string proxy_type;
			int poll_interval;
			int wait_retry;
			int bind_port_start;
			int bind_port_end;
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
