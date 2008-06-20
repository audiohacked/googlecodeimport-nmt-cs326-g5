#ifndef __TORRENT_MANAGER_H
#define __TORRENT_MANAGER_H
	#include <wx/wxprec.h>

	#ifndef WX_PRECOMP
		#include <wx/wx.h>
	#endif
/*
	#include <boost/filesystem/operations.hpp>
	#include <boost/filesystem/convenience.hpp>
	#include <boost/filesystem/fstream.hpp>
	#include <boost/filesystem/exception.hpp>
	#include <boost/bind.hpp>
	#include <boost/program_options.hpp>
	#include <boost/regex.hpp>

*/
	#include <libtorrent/config.hpp>
	#include <libtorrent/fingerprint.hpp>
	#include <libtorrent/entry.hpp>
	#include <libtorrent/bencode.hpp>
	#include <libtorrent/session.hpp>
	#include <libtorrent/extensions/metadata_transfer.hpp>
	#include <libtorrent/extensions/ut_pex.hpp>
	
	#include <libtorrent/peer_id.hpp>
	
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
	using namespace libtorrent;

	typedef std::multimap<std::string, libtorrent::torrent_handle> handles_t;

	class TorrentTransferManager : public session
	{
		public:
			//Transfer activeTransfers;
			//Transfer inactiveTransfers;
			//fingerprint FingerPrint;
			/* Digital Distribution and Publishing System; 
				bittorrent client id string; version 1.0.0.0 */
			//fingerprint torrentClientFingerprint = fingerprint("DD", 1, 0, 0, 0);
			//curlHandle transferHandle;
			
			session torrentSession;
			session_settings torrentSessionSettings;
			session_status torrentSessionStatus;
			handles_t handles;
			add_torrent_params torrentAddData;

			TorrentTransferManager();
			~TorrentTransferManager();
			torrent_handle AddTorrent(char const* tracker, big_number const& hash);
			bool startTransfer();
			bool cancelTransfer();
			bool pauseTransfer();
			bool finishTransfer();
			bool connectToPeers();
			bool downloadTorrent();
			bool uploadTorrent();
			bool setTransferSpeed();
			int getSessionStatus();
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
