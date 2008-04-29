#ifndef __TRANSFER_MANAGER_H
#define __TRANSFER_MANAGER_H
	#include <wx/wxprec.h>

	#ifndef WX_PRECOMP
		#include <wx/wx.h>
	#endif
	
	#include <wx/listctrl.h>
	
	class TransferManager : public wxPanel
	{
		public:
			TransferManager(wxWindow* parent, wxWindowID id, 
                    const wxPoint& pos, const wxSize& size, long style);
			wxListCtrl *listDownloads;
			void AddTorrentDownload();
			void AddHttpDownload();

	};
		
#endif

