#ifndef __TRANSFER_MANAGER_H
#define __TRANSFER_MANAGER_H
	#include <wx/wxprec.h>

	#ifndef WX_PRECOMP
		#include <wx/wx.h>
	#endif
	
	#include <wx/listctrl.h>

	//#include "HttpManager.h"
	#include "TransferTimer.h"
	#include "TransferManagerList.h"
	
	class TransferManager : public wxPanel
	{
		public:
			TransferManager(wxWindow* parent, wxWindowID id, 
				const wxPoint& pos, const wxSize& size, long style);
			~TransferManager();
			
			void OnItemRightClick(wxListEvent &event);
			void OnMenuUpdateItem(wxCommandEvent &event);
			
			void OnContextMenu(wxContextMenuEvent &event);
			void OnMenuAddTorrent(wxCommandEvent &event);
			void OnMenuAddHttpDownload(wxCommandEvent &event);
			
			void OnItemDeselected(wxListEvent &event);
			void OnItemSelected(wxListEvent &event);
			void OnMenuStartItem(wxCommandEvent &event);
			void OnMenuStopItem(wxCommandEvent &event);
			void OnMenuPauseItem(wxCommandEvent &event);
			void OnMenuTorrentProperties(wxCommandEvent &event);

			TransferManagerList *listDownloads;
			TransferManagerTimer *timer;
			long m_SelectedItem;
			bool b_ItemSelected;

			#ifdef __HTTP_MANAGER_H
				int AddHttpDownload(wxString downloadURL);
			#endif

			DECLARE_EVENT_TABLE()
	};
	
#endif
