#include <QtGui>
#include <QObject>
#include "AppConfig.h"

DDPSConfig::DDPSConfig(): QSettings("./rc_ddps", QSettings::IniFormat)
{
	//Load();
	qDebug() << "Settings Configuration";
}

void DDPSConfig::Save()
{
	qDebug("Saving Config File");
	if (cfg_RememberLogin)
	{
		cfg_LoginUsername;
		cfg_LoginPassword;
	}
	else
	{
		cfg_LoginUsername = QString("");
		cfg_LoginPassword = QString("");
	}

	setValue("/GUI/LoginUsername", cfg_LoginUsername);
	setValue("/GUI/LoginPassword", cfg_LoginPassword); // in md5/sha1 hash format
	setValue("/GUI/RememberLogin", cfg_RememberLogin);
	setValue("/GUI/GuiResourceFile", cfg_GuiResourceFile);
	setValue("/GUI/GuiStyleSheet", cfg_GuiStyleSheet);
	setValue("/GUI/GuiSkin", cfg_GuiSkin);

	// Transfer
	setValue("/Transfers/download_location", cfg_download_location);
	setValue("/Transfers/proxy", cfg_proxy);
	setValue("/Transfers/proxy_login", cfg_proxy_login);
	setValue("/Transfers/proxy_type", cfg_proxy_type);

	// HTTP Transfer

	// BitTorrent
	setValue("/BitTorrent/download_speed", cfg_download_speed);
	setValue("/BitTorrent/upload_speed", cfg_upload_speed);
	setValue("/BitTorrent/max_peers", cfg_max_peers);
	setValue("/BitTorrent/listen_port", cfg_listen_port);
	setValue("/BitTorrent/upload_slots_limit", cfg_upload_slots_limit);
	setValue("/BitTorrent/half_open_limit", cfg_half_open_limit);
	setValue("/BitTorrent/poll_interval", cfg_poll_interval);
	setValue("/BitTorrent/wait_retry", cfg_wait_retry);
	setValue("/BitTorrent/bind_port_start", cfg_bind_port_start);
	setValue("/BitTorrent/bind_port_end", cfg_bind_port_end);
	setValue("/BitTorrent/preferred_ratio", cfg_preferred_ratio);
	setValue("/BitTorrent/log_level", cfg_log_level);
	setValue("/BitTorrent/ipfilter_file", cfg_ipfilter_file);
	setValue("/BitTorrent/allocation_mode", cfg_allocation_mode);

}

void DDPSConfig::Load()
{
	qDebug("Loading Config File");
	cfg_RememberLogin = value("/GUI/RememberLogin", false).toBool();
	cfg_LoginUsername = value("/GUI/LoginUsername", "").toString();
	cfg_LoginPassword = value("/GUI/LoginPassword", "").toString();
	cfg_GuiResourceFile = value("/GUI/GuiResourceFile", "default").toString();
	cfg_GuiStyleSheet = value("/GUI/GuiStyleSheet", "default").toString();
	cfg_GuiSkin = value("/GUI/GuiSkin", "default").toString();

	// Transfer
	cfg_download_location = value("/Transfers/download_location", "./download-files/").toString();
	cfg_proxy= value("/Transfers/proxy", "").toString();
	cfg_proxy_login = value("/Transfers/proxy_login", "").toString();
	cfg_proxy_type = value("/Transfers/proxy_type", "socks5").toString();

	// HTTP Transfer

	// BitTorrent
	cfg_download_speed = value("/BitTorrent/download_speed", 200).toInt();
	cfg_upload_speed = value("/BitTorrent/upload_speed", 190).toInt();
	cfg_max_peers = value("/BitTorrent/max_peers", 30).toInt();
	cfg_listen_port = value("/BitTorrent/listen_port", 6881).toInt();
	cfg_upload_slots_limit = value("/BitTorrent/upload_slots_limit", 3).toInt();
	cfg_half_open_limit = value("/BitTorrent/half_open_limit", 10).toInt();
	cfg_poll_interval = value("/BitTorrent/poll_interval", 2).toInt();
	cfg_wait_retry = value("/BitTorrent/wait_retry", 30).toInt();
	cfg_bind_port_start = value("/BitTorrent/bind_port_start", 0).toInt();
	cfg_bind_port_end = value("/BitTorrent/bind_port_end", 0).toInt();
	cfg_preferred_ratio = value("/BitTorrent/preferred_ratio", 200).toInt();
	cfg_log_level = value("/BitTorrent/log_level", "info").toString();
	cfg_ipfilter_file = value("/BitTorrent/ipfilter_file", "").toString();
	cfg_allocation_mode = value("/BitTorrent/allocation_mode", "full").toString();
}
