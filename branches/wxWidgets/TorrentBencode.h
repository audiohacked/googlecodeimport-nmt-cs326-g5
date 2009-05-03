#ifndef __TORRENT_BENCODE_H
#define __TORRENT_BENCODE_H

	#include <wx/wxprec.h>

	#ifndef WX_PRECOMP
		#include <wx/wx.h>
	#endif

	#include <wx/datstrm.h>
	#include <wx/wfstream.h>
	#include <wx/ffile.h>
	#include <wx/txtstrm.h>

	#include <boost/lexical_cast.hpp>

	#include <libtorrent/config.hpp>
	#include <libtorrent/entry.hpp>

	int wx_bdecode(wxFileInputStream &file, wxDataInputStream &data, libtorrent::entry &ret, int depth);
	void wx_bencode(wxDataOutputStream &out_data, wxTextOutputStream &out_text, libtorrent::entry e);

#endif
