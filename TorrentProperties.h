#ifndef __TORRENT_PROPERTIES_H
#define __TORRENT_PROPERTIES_H

	#include <wx/string.h>
	#include <wx/dialog.h>

	#include <libtorrent/session.hpp>

	class TorrentProperties : public wxDialog
	{
		public:
			TorrentProperties(wxString const& title, libtorrent::torrent_handle &h);
			~TorrentProperties();
		private:
			void TorrentInformation();
			void TorrentCreator();

			libtorrent::torrent_handle &handle;
			libtorrent::torrent_status s;
			libtorrent::torrent_info const& i;
			
			wxStaticText *tor_header_info;
			wxStaticText *tor_name_label;
			wxStaticText *tor_name;
			wxStaticText *tor_size_label;
			wxStaticText *tor_size;
			wxStaticText *tor_tracker_label;
			wxTextCtrl *tor_tracker;
			wxStaticText *tor_hash_label;
			wxStaticText *tor_hash;
			wxStaticText *tor_secure_label;
			wxStaticText *tor_secure;
			wxStaticText *tor_comment_label;
			wxTextCtrl *tor_comment;
			
			wxStaticText *tor_header_creator;
			wxStaticText *tor_creator_label;
			wxStaticText *tor_creator;
			wxStaticText *tor_date_label;
			wxStaticText *tor_date;
			
	};

	//libtorrent::torrent_info &TorrentProperties::i = 0;
#endif
