#include <wx/wxprec.h>

#ifndef WX_PRECOMP
	#include <wx/wx.h>
#endif

#include <wx/listctrl.h>
#include <wx/progdlg.h>
#include <wx/utils.h>
#include <wx/sysopt.h>

#include "HttpManager.h"


#include "AppEnum.h"
#include "AppCommon.h"
#include "TransferCommon.h"
#include "TransferTimer.h"
#include "TransferManagerList.h"
#include "TransferManager.h"
#include "TorrentProperties.h"

/*enum
{
	TORRENT_Properties
};*/

BEGIN_EVENT_TABLE( TransferManager, wxPanel )
	EVT_LIST_ITEM_RIGHT_CLICK(LIST_DownloadManager, TransferManager::OnItemRightClick)
	EVT_LIST_ITEM_DESELECTED(LIST_DownloadManager, TransferManager::OnItemDeselected)
	EVT_LIST_ITEM_SELECTED(LIST_DownloadManager, TransferManager::OnItemSelected)
	//EVT_CONTEXT_MENU(TransferManager::OnContextMenu)
	//EVT_MENU(MENU_TorrentDownload, TransferManager::OnMenuAddTorrent)
	//EVT_MENU(MENU_HTTPDownload, TransferManager::OnMenuAddHttpDownlaod)
	EVT_MENU(MENU_UpdateItem, TransferManager::OnMenuUpdateItem)
	EVT_MENU(MENU_StartItem, TransferManager::OnMenuStartItem)
	EVT_MENU(MENU_StopItem, TransferManager::OnMenuStopItem)
	EVT_MENU(MENU_PauseItem, TransferManager::OnMenuPauseItem)
	EVT_MENU(TORRENT_Properties, TransferManager::OnMenuTorrentProperties)
END_EVENT_TABLE()

TransferManager::TransferManager(wxWindow* parent, wxWindowID id,
const wxPoint& pos, const wxSize& size, long style) : wxPanel(parent, id, pos, size, style)
{
	listDownloads = new TransferManagerList( this, LIST_DownloadManager, wxDefaultPosition, wxDefaultSize, wxLC_REPORT|wxLC_VIRTUAL );
	timer = new TransferManagerTimer(listDownloads);
	timer->start();
	
	b_ItemSelected = false;

	wxSystemOptions opts;
	opts.SetOption(wxT("mac.listctrl.always_use_generic"), 1);

	wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);
	sizer->Add(listDownloads, 1, wxEXPAND|wxALL, 5);
	SetSizer(sizer);
	sizer->SetSizeHints(this);
}

TransferManager::~TransferManager()
{
	timer->Stop();
}

void TransferManager::OnItemDeselected(wxListEvent &event)
{
	b_ItemSelected = false;
}

void TransferManager::OnItemSelected(wxListEvent &event)
{
	b_ItemSelected = true;
	m_SelectedItem = event.GetItem();
}

void TransferManager::OnMenuStartItem(wxCommandEvent &event)
{
	if (b_ItemSelected)
	{
		libtorrent::torrent_handle h;
		download_handles_t::const_iterator torItem = listDownloads->list.find(m_SelectedItem);
		if (torItem->first == m_SelectedItem)
	 		h = torItem->second.torrent_list().handle;

		if (h.is_valid())
		{
			if (h.is_paused())
				h.resume();
		}
	}
}

void TransferManager::OnMenuStopItem(wxCommandEvent &event)
{
	
}

void TransferManager::OnMenuPauseItem(wxCommandEvent &event)
{
	if (b_ItemSelected)
	{
		libtorrent::torrent_handle h;
		download_handles_t::const_iterator torItem = listDownloads->list.find(m_SelectedItem);
		if (torItem->first == m_SelectedItem)
	 		h = torItem->second.torrent_list().handle;

		if (h.is_valid())
		{
			if (!h.is_paused())
				h.pause();
		}
	}
}

void TransferManager::OnItemRightClick(wxListEvent &event)
{
	//b_ItemSelected = true;
	m_SelectedItem = event.GetItem();
	
	wxMenu *ItemMenu = new wxMenu();
	ItemMenu->Append(MENU_UpdateItem, wxT("Update Item"));
	ItemMenu->Append(MENU_RemoveItem, wxT("Remove Item"));
	ItemMenu->AppendSeparator();
	ItemMenu->Append(MENU_StartItem, wxT("Start Item"));
	ItemMenu->Append(MENU_StopItem, wxT("Stop Item"));
	ItemMenu->Append(MENU_PauseItem, wxT("Pause Item"));
	ItemMenu->AppendSeparator();
	ItemMenu->Append(-1, wxT("Item Queue - Move Up"));
	ItemMenu->Append(-1, wxT("Item Queue - Move Down"));
	ItemMenu->Append(-1, wxT("Item Queue - Move Top"));
	ItemMenu->Append(-1, wxT("Item Queue - Move Bottom"));
	ItemMenu->AppendSeparator();
	ItemMenu->Append(TORRENT_Properties, wxT("Item Properties"));
	
	PopupMenu(ItemMenu);
}

void TransferManager::OnMenuUpdateItem(wxCommandEvent &event)
{
	if (b_ItemSelected)
	{
		//listDownloads->RefreshItem(m_SelectedItem);
		libtorrent::torrent_handle h;
		download_handles_t::const_iterator torItem = listDownloads->list.find(m_SelectedItem);
		if (torItem->first == m_SelectedItem)
	 		h = torItem->second.torrent_list().handle;

		if (h.is_valid())
		{
			h.force_recheck();
		}
	}
}

void TransferManager::OnContextMenu(wxContextMenuEvent &event)
{
	if (!b_ItemSelected)
	{
		wxMenu *contextMenu = new wxMenu();

		contextMenu->Append(MENU_TorrentDownload, wxT("Add Torrent"));
		contextMenu->Append(MENU_HTTPDownload, wxT("Add HTTP Download"));

		PopupMenu(contextMenu);
	}
}

void TransferManager::OnMenuAddTorrent(wxCommandEvent &event)
{
	/*int answer = listDownloads->AddTorrentDownload(
		"OOo_2.4.1_MacOSXIntel_install_en-US",
		"http://www.ooodev.org:6969/",
		"cdb13e1d5c15e768a0244f858e88df746a475d8b"
	);*/
	int answer = listDownloads->AddTorrentFileDownload(
		"original.torrent"
	);
	
	if(answer == wxCANCEL)
		event.Skip();
}

void TransferManager::OnMenuAddHttpDownload(wxCommandEvent &event)
{
	int answer = listDownloads->httpDownloads->AddDownload(
		wxT("http://gentoo.osuosl.org/releases/x86/2008.0_beta2/installcd/install-x86-minimal-2008.0_beta2.iso")
	);
	if(answer == wxOK)
		event.Skip();
}

void TransferManager::OnMenuTorrentProperties(wxCommandEvent &event)
{
	if (b_ItemSelected)
	{
		//listDownloads->RefreshItem(m_SelectedItem);
		libtorrent::torrent_handle h;
		download_handles_t::const_iterator torItem = listDownloads->list.find(m_SelectedItem);
		if (torItem->first == m_SelectedItem)
	 		h = torItem->second.torrent_list().handle;

		if (h.is_valid())
		{
			TorrentProperties prop(wxString(h.name().c_str(), wxConvUTF8), h);
			prop.ShowModal();
		}
	}
}