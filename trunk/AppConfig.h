#ifndef __APP_CONFIG_H
#define __APP_CONFIG_H

	#include <wx/fileconf.h>
	#include <wx/string.h>

	class DDPSConfig : public wxFileConfig
	{
		public:
			DDPSConfig();
			~DDPSConfig();

			void Save();
			void Load();

			wxFileConfig *m_cfg;
			wxString m_configfile;

			// GUI
			bool cfg_RememberLogin;
			wxString cfg_LoginUsername;
			wxString cfg_LoginPassword;

			// Transfer
			wxString cfg_download_location;
			wxString cfg_proxy;
			wxString cfg_proxy_login;
			wxString cfg_proxy_type;

			// HTTP Transfer

			// BitTorrent
			wxString cfg_log_level;
			wxString cfg_ipfilter_file;
			wxString cfg_allocation_mode;
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
	};
#endif
