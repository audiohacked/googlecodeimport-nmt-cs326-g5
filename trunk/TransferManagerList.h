#ifndef __TRANSFER_MANAGER_LIST_H
#define __TRANSFER_MANAGER_LIST_H
	#include <wx/wxprec.h>

	#ifndef WX_PRECOMP
		#include <wx/wx.h>
	#endif

	#include "TorrentManager.h"
	#include "HttpManager.h"

	class TransferManagerList : public wxListCtrl
	{
		public:
			TransferManagerList(wxWindow* parent, wxWindowID id,
				const wxPoint& pos, const wxSize& size, long style);
			//~TransferManagerList();
			virtual wxString OnGetItemText(long item, long column) const;
			wxString GetTorrentItemText(long item, long column) const;

			long int listIndex;
			download_handles_t list;

			#ifdef __TORRENT_MANAGER_H
				TorrentTransferManager *torrentDownloads;
				libtorrent::torrent_handle tor;
				int AddTorrentDownload(char const* name, char const* tracker, char const* TorrentHash);
				int AddTorrentMagnetDownload(char const* uri);
				int AddTorrentFileDownload(char const* file);
			#endif
		
			#ifdef __HTTP_MANAGER_H
				HttpTransferManager *httpDownloads;
			#endif

	};

#endif
