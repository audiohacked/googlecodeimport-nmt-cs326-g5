#ifndef __TORRENT_COMMON_H
#define __TORRENT_COMMON_H

	#include <wx/wxprec.h>

	#ifndef WX_PRECOMP
		#include <wx/wx.h>
	#endif

	#include <wx/progdlg.h>
	
	#include <libtorrent/config.hpp>
	#include <libtorrent/entry.hpp>
	#include <libtorrent/session.hpp>

	typedef struct /*wx_torrent_data*/ {
		wxProgressDialog *dlg;
		libtorrent::torrent_handle handle;
	} torrent_data_t;

	//typedef std::map<libtorrent::torrent_handle, wxProgressDialog*> torrent_data_t;
	typedef std::map<std::string, torrent_data_t> handles_t;

#endif
