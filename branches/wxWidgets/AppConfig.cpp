#include <wx/wxprec.h>

#ifndef WX_PRECOMP
#	include <wx/wx.h>
#endif

//	#include <wx/datstrm.h>
#include <wx/wfstream.h>
//	#include <wx/ffile.h>
//	#include <wx/txtstrm.h>

#include "AppConfig.h"

DDPSConfig::DDPSConfig()
{
	wxFile *conf_file;
	m_configfile = wxT(".ddps_rc");

	if (!wxFile::Exists(m_configfile))
	{
		conf_file = new wxFile();
		conf_file->Create(m_configfile);
		conf_file->Close();
	}

	wxFileInputStream input_config_file( m_configfile );

	m_cfg = new wxFileConfig( (wxInputStream&)input_config_file );

	Load();
}

DDPSConfig::~DDPSConfig()
{
	delete wxConfigBase::Set((wxConfigBase*)NULL);
}

void DDPSConfig::Save()
{
	if (cfg_RememberLogin)
	{
		cfg_LoginUsername;
		cfg_LoginPassword;
	}
	else
	{
		cfg_LoginUsername = wxT("");
		cfg_LoginPassword = wxT("");
	}
	
	m_cfg->Write(wxT("/GUI/LoginUsername"), cfg_LoginUsername);
	m_cfg->Write(wxT("/GUI/LoginPassword"), cfg_LoginPassword); // in md5/sha1 hash format
	m_cfg->Write(wxT("/GUI/RememberLogin"), (bool)cfg_RememberLogin);

	// Transfer
	m_cfg->Write(wxT("/Transfers/download_location"), cfg_download_location);
	m_cfg->Write(wxT("/Transfers/proxy"), cfg_proxy);
	m_cfg->Write(wxT("/Transfers/proxy_login"), cfg_proxy_login);
	m_cfg->Write(wxT("/Transfers/proxy_type"), cfg_proxy_type);

	// HTTP Transfer

	// BitTorrent
	m_cfg->Write(wxT("/BitTorrent/download_speed"), (int)cfg_download_speed);
	m_cfg->Write(wxT("/BitTorrent/upload_speed"), (int)cfg_upload_speed);
	m_cfg->Write(wxT("/BitTorrent/max_peers"), (int)cfg_max_peers);
	m_cfg->Write(wxT("/BitTorrent/listen_port"), (int)cfg_listen_port);
	m_cfg->Write(wxT("/BitTorrent/upload_slots_limit"), (int)cfg_upload_slots_limit);
	m_cfg->Write(wxT("/BitTorrent/half_open_limit"), (int)cfg_half_open_limit);
	m_cfg->Write(wxT("/BitTorrent/poll_interval"), (int)cfg_poll_interval);
	m_cfg->Write(wxT("/BitTorrent/wait_retry"), (int)cfg_wait_retry);
	m_cfg->Write(wxT("/BitTorrent/bind_port_start"), (int)cfg_bind_port_start);
	m_cfg->Write(wxT("/BitTorrent/bind_port_end"), (int)cfg_bind_port_end);
	m_cfg->Write(wxT("/BitTorrent/preferred_ratio"), (int)cfg_preferred_ratio);
	m_cfg->Write(wxT("/BitTorrent/log_level"), cfg_log_level);
	m_cfg->Write(wxT("/BitTorrent/ipfilter_file"), cfg_ipfilter_file);
	m_cfg->Write(wxT("/BitTorrent/allocation_mod"), cfg_allocation_mode);
	
	wxFileOutputStream output_config_file(m_configfile);
	m_cfg->Save(output_config_file);
}

void DDPSConfig::Load()
{
	m_cfg->Read(wxT("/GUI/RememberLogin"), &cfg_RememberLogin, false);
	m_cfg->Read(wxT("/GUI/LoginUsername"), &cfg_LoginUsername, wxT(""));
	m_cfg->Read(wxT("/GUI/LoginPassword"), &cfg_LoginPassword, wxT(""));

	// Transfer
	m_cfg->Read(wxT("/Transfers/download_location"), &cfg_download_location, wxT("./download-files/"));
	m_cfg->Read(wxT("/Transfers/proxy"), &cfg_proxy, wxT(""));
	m_cfg->Read(wxT("/Transfers/proxy_login"), &cfg_proxy_login, wxT(""));
	m_cfg->Read(wxT("/Transfers/proxy_type"), &cfg_proxy_type, wxT("socks5"));

	// HTTP Transfer

	// BitTorrent
	m_cfg->Read(wxT("/BitTorrent/download_speed"), &cfg_download_speed, 200);
	m_cfg->Read(wxT("/BitTorrent/upload_speed"), &cfg_upload_speed, 190);
	m_cfg->Read(wxT("/BitTorrent/max_peers"), &cfg_max_peers, 30);
	m_cfg->Read(wxT("/BitTorrent/listen_port"), &cfg_listen_port, 6881);
	m_cfg->Read(wxT("/BitTorrent/upload_slots_limit"), &cfg_upload_slots_limit, 3);
	m_cfg->Read(wxT("/BitTorrent/half_open_limit"), &cfg_half_open_limit, 10);
	m_cfg->Read(wxT("/BitTorrent/poll_interval"), &cfg_poll_interval, 2);
	m_cfg->Read(wxT("/BitTorrent/wait_retry"), &cfg_wait_retry, 30);
	m_cfg->Read(wxT("/BitTorrent/bind_port_start"), &cfg_bind_port_start, 0);
	m_cfg->Read(wxT("/BitTorrent/bind_port_end"), &cfg_bind_port_end, 0);
	m_cfg->Read(wxT("/BitTorrent/preferred_ratio"), &cfg_preferred_ratio, 200);
	m_cfg->Read(wxT("/BitTorrent/log_level"), &cfg_log_level, wxT("info"));
	m_cfg->Read(wxT("/BitTorrent/ipfilter_file"), &cfg_ipfilter_file, wxT(""));
	m_cfg->Read(wxT("/BitTorrent/allocation_mod"), &cfg_allocation_mode, wxT("full"));
}
