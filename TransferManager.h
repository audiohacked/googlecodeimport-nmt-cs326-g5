#ifndef __TRANSFER_MANAGER_H
#define __TRANSFER_MANAGER_H
	#include <wx/wxprec.h>

	#ifndef WX_PRECOMP
		#include <wx/wx.h>
	#endif
	
	#include <wx/listctrl.h>
	#include <wx/progdlg.h>
	#include <wx/utils.h>
	#include <wx/sysopt.h>

	#include "TorrentManager.h"
	#include "HttpManager.h"

	//#include <map>
	//#include <utility>
	
	/*typedef union {
		torrent_handles_t *TorrentDownloadList;
		http_handles_t *HttpDownloadList;
	} download_list_t;
			
	typedef std::map<long, download_list_t> download_handles_t;*/
	
	#include "TransferCommon.h"
	
	class TransferManagerList : public wxListCtrl
	{
		public:
			TransferManagerList(wxWindow* parent, wxWindowID id,
				const wxPoint& pos, const wxSize& size, long style);
			virtual wxString OnGetItemText(long item, long column) const;
			wxString GetTorrentItemText(long item, long column) const;
			long int listIndex;
			wxArrayString state_str;
			download_handles_t list;

			#ifdef __TORRENT_MANAGER_H
				TorrentTransferManager *torrentDownloads;
				libtorrent::torrent_handle tor;
				int AddTorrentDownload(char const* name, char const* tracker, char const* TorrentHash);
			#endif
			
			#ifdef __HTTP_MANAGER_H
				HttpTransferManager *httpDownloads;
			#endif

	};
	
	class TransferManager : public wxPanel
	{
		public:
			TransferManager(wxWindow* parent, wxWindowID id, 
				const wxPoint& pos, const wxSize& size, long style);
			void OnContextMenu(wxContextMenuEvent &event);
			void OnMenuAddTorrent(wxCommandEvent &event);
			void OnMenuAddHttpDownlaod(wxCommandEvent &event);

			TransferManagerList *listDownloads;

			#ifdef __HTTP_MANAGER_H
				int AddHttpDownload(wxString downloadURL);
			#endif

			DECLARE_EVENT_TABLE()
	};
	
#endif

