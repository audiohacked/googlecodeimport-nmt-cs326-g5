#ifndef __TORRENT_PROPERTIES_H
#define __TORRENT_PROPERTIES_H
#include <QtGui>
	class TorrentProperties : public QDialog
	{
		public:
			TorrentProperties(QString const& title, libtorrent::torrent_handle &h, QWidget *parent);
			~TorrentProperties();
		private:
			void TorrentInformation();
			void TorrentCreator();

			libtorrent::torrent_handle &handle;
			libtorrent::torrent_status s;
			libtorrent::torrent_info const& i;
			
			QLabel *tor_header_info;
			QLabel *tor_name_label;
			QLabel *tor_name;
			QLabel *tor_size_label;
			QLabel *tor_size;
			QLabel *tor_tracker_label;
			QLineEdit *tor_tracker;
			QLabel *tor_hash_label;
			QLabel *tor_hash;
			QLabel *tor_secure_label;
			QLabel *tor_secure;
			QLabel *tor_comment_label;
			QLineEdit *tor_comment;
			
			QLabel *tor_header_creator;
			QLabel *tor_creator_label;
			QLabel *tor_creator;
			QLabel *tor_date_label;
			QLabel *tor_date;
			
	};

	//libtorrent::torrent_info &TorrentProperties::i = 0;
#endif
