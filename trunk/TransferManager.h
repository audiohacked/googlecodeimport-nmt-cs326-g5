#ifndef __TRANSFER_MANAGER_H
#define __TRANSFER_MANAGER_H
	#include <wx/wxprec.h>

	#ifndef WX_PRECOMP
		#include <wx/wx.h>
	#endif
	
	#include <wx/listctrl.h>

	#include "TorrentManager.h"
	#include "HttpManager.h"
	
	class TransferManager : public wxPanel
	{
		public:
			TransferManager(wxWindow* parent, wxWindowID id, 
                    const wxPoint& pos, const wxSize& size, long style);

			wxListCtrl *listDownloads;
			TorrentTransferManager *torrentDownloads;
			HttpTransferManager *httpDownloads;
			
			void AddTorrentDownload(big_number const& TorrentHash);
			void AddHttpDownload();

	};
		
#endif

