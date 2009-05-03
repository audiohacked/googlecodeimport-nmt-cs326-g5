#ifndef __APP_CONFIG_H
#define __APP_CONFIG_H

	#include <QtGui>

	class DDPSConfig : public QSettings
	{
		Q_OBJECT
		public:
			DDPSConfig();
			//~DDPSConfig();

			QSettings *m_cfg;
			QString m_configfile;

			// GUI
			bool cfg_RememberLogin;
			QString cfg_LoginUsername;
			QString cfg_LoginPassword;

			// Transfer
			QString cfg_download_location;
			QString cfg_proxy;
			QString cfg_proxy_login;
			QString cfg_proxy_type;

			// HTTP Transfer

			// BitTorrent
			QString cfg_log_level;
			QString cfg_ipfilter_file;
			QString cfg_allocation_mode;
			int cfg_download_speed;
			int cfg_upload_speed;
			int cfg_max_peers;
			int cfg_listen_port;
			int cfg_upload_slots_limit;
			int cfg_half_open_limit;
			int cfg_poll_interval;
			int cfg_wait_retry;
			int cfg_bind_port_start;
			int cfg_bind_port_end;
			int cfg_preferred_ratio; // float for libtorrent (divide by 100)
		public slots:
			void Save();
			void Load();
	};
#endif
