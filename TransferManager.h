#ifndef __TRANSFER_MANAGER_H
#define __TRANSFER_MANAGER_H
	#include <wx/wxprec.h>

	#ifndef WX_PRECOMP
		#include <wx/wx.h>
	#endif
	
	#include <wx/listctrl.h>
	#include <wx/progdlg.h>
	#include <wx/utils.h>

	#include "TorrentManager.h"
	#include "HttpManager.h"
	
	class TransferManager : public wxPanel
	{
		public:
			TransferManager(wxWindow* parent, wxWindowID id, 
				const wxPoint& pos, const wxSize& size, long style);
			void OnContextMenu(wxContextMenuEvent &event);
			void OnMenuAddTorrent(wxCommandEvent &event);
			void OnMenuAddHttpDownlaod(wxCommandEvent &event);

			wxListCtrl *listDownloads;
			long int listIndex;
						
			#ifdef __TORRENT_MANAGER_H
				TorrentTransferManager *torrentDownloads;
				libtorrent::torrent_handle tor;
				int AddTorrentDownload(char const* name, char const* tracker, char const* TorrentHash);
			#endif
			
			#ifdef __HTTP_MANAGER_H
				HttpTransferManager *httpDownloads;
				int AddHttpDownload(wxString downloadURL);
			#endif

			DECLARE_EVENT_TABLE()
	};
		
#endif

