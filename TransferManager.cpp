#include "enum.h"
#include "common.h"
#include "TransferCommon.h"
#include "TransferTimer.h"
#include "TransferManager.h"


BEGIN_EVENT_TABLE( TransferManager, wxPanel )
	EVT_CONTEXT_MENU(TransferManager::OnContextMenu)
	EVT_MENU(MENU_TorrentDownload, TransferManager::OnMenuAddTorrent)
	EVT_MENU(MENU_HTTPDownload, TransferManager::OnMenuAddHttpDownlaod)
	EVT_LIST_ITEM_RIGHT_CLICK(LIST_DownloadManager, TransferManager::OnItemRightClick)
	EVT_MENU(MENU_UpdateItem, TransferManager::OnMenuUpdateItem)
	EVT_LIST_ITEM_DESELECTED(LIST_DownloadManager, TransferManager::OnItemDeselected)
	EVT_LIST_ITEM_SELECTED(LIST_DownloadManager, TransferManager::OnItemSelected)
END_EVENT_TABLE()

TransferManager::TransferManager(wxWindow* parent, wxWindowID id,
const wxPoint& pos, const wxSize& size, long style) : wxPanel(parent, id, pos, size, style)
{
	listDownloads = new TransferManagerList( this, LIST_DownloadManager, wxDefaultPosition, wxDefaultSize, wxLC_REPORT|wxLC_VIRTUAL );
	TransferManagerTimer *timer = new TransferManagerTimer(listDownloads);
	timer->start();
	
	b_ItemSelected = false;

	wxSystemOptions opts;
	opts.SetOption(wxT("mac.listctrl.always_use_generic"), 1);

	wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);
	sizer->Add(listDownloads, 1, wxEXPAND|wxALL, 5);
	SetSizer(sizer);
	sizer->SetSizeHints(this);
}

void TransferManager::OnItemDeselected(wxListEvent &event)
{
	b_ItemSelected = false;
}

void TransferManager::OnItemSelected(wxListEvent &event)
{
	b_ItemSelected = true;
}

void TransferManager::OnItemRightClick(wxListEvent &event)
{
	//b_ItemSelected = true;
	m_SelectedItem = event.GetItem();
	
	wxMenu *ItemMenu = new wxMenu();
	ItemMenu->Append(MENU_UpdateItem, wxT("Update Item"));
	ItemMenu->Append(MENU_RemoveItem, wxT("Remove Item"));
	//ItemMenu->Append(MENU_TorrentDownload, wxT("Add Torrent"));
	//ItemMenu->Append(MENU_HTTPDownload, wxT("Add HTTP Download"));
	PopupMenu(ItemMenu);
}

void TransferManager::OnMenuUpdateItem(wxCommandEvent &event)
{
	listDownloads->RefreshItem(m_SelectedItem);
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
	int answer = listDownloads->AddTorrentDownload(
		"knoppix dvd v5.3 English",
		"http://torrent.unix-ag.uni-kl.de/announce",
		"396fcb0f80514a92306c2e8e00395fda8db36f9b"
	);
	if(answer == wxCANCEL)
		event.Skip();
}

void TransferManager::OnMenuAddHttpDownlaod(wxCommandEvent &event)
{
	int answer = listDownloads->httpDownloads->AddDownload(
		wxT("http://gentoo.osuosl.org/releases/x86/2008.0_beta2/installcd/install-x86-minimal-2008.0_beta2.iso")
	);
	if(answer == wxOK)
		event.Skip();
}

TransferManagerList::TransferManagerList(wxWindow* parent, wxWindowID id,
	const wxPoint& pos=wxDefaultPosition, const wxSize& size=wxDefaultSize,
	long style=wxLC_REPORT|wxLC_VIRTUAL) : wxListCtrl(parent, id, pos, size, style)
{
	listIndex = 0;

#ifdef __TORRENT_MANAGER_H
	torrentDownloads = new TorrentTransferManager(&list);
#endif

#ifdef __HTTP_MANAGER_H
	httpDownloads = new HttpTransferManager(&list);
#endif 

	InsertColumn(0, wxT("Name"), wxLIST_FORMAT_LEFT, 60);
	InsertColumn(1, wxT("Size"), wxLIST_FORMAT_LEFT, 60);
	InsertColumn(2, wxT("Progress"), wxLIST_FORMAT_LEFT, 80);
	InsertColumn(3, wxT("Status"), wxLIST_FORMAT_LEFT, 70);
	InsertColumn(4, wxT("Down Speed"), wxLIST_FORMAT_LEFT, 100);
	InsertColumn(5, wxT("Up Speed"), wxLIST_FORMAT_LEFT, 80);
	InsertColumn(6, wxT("ETA"), wxLIST_FORMAT_LEFT, 60);
	InsertColumn(7, wxT("Downloaded"), wxLIST_FORMAT_LEFT, 100);
	InsertColumn(8, wxT("Uploaded"), wxLIST_FORMAT_LEFT, 80);
	InsertColumn(9, wxT("Peers"), wxLIST_FORMAT_LEFT, 60);
	InsertColumn(10, wxT("Seeds"), wxLIST_FORMAT_LEFT, 60);
	InsertColumn(11, wxT("Copies"), wxLIST_FORMAT_LEFT, 60);

	try
	{
		state_str.Add(wxString( 	wxT("checking queue") 	));
		state_str.Add(wxString( 	wxT("checking files") 	));
		state_str.Add(wxString( 	wxT("connecting") 		));
		state_str.Add(wxString( 	wxT("dl metadata") 		));
		state_str.Add(wxString( 	wxT("downloading") 		));
		state_str.Add(wxString( 	wxT("finished") 		));
		state_str.Add(wxString( 	wxT("seeding") 			));
		state_str.Add(wxString( 	wxT("allocating") 		)); 
	} catch(std::exception&) {}

}

#ifdef __TORRENT_MANAGER_H
int TransferManagerList::AddTorrentDownload(char const* name, char const* tracker, char const* TorrentHash)
{
	libtorrent::sha1_hash tor_info_hash = boost::lexical_cast<libtorrent::sha1_hash>(TorrentHash);
	SetItemCount(listIndex+1);
	tor = torrentDownloads->AddTorrent(name, tracker, tor_info_hash, listIndex);
	listIndex++;

	return wxOK;
}
#endif

wxString TransferManagerList::OnGetItemText(long item, long column) const
{
	download_handles_t::const_iterator grabItem = list.find(item);
	if (grabItem->second.type() == download_list::torrent_list_t)
	{
		return GetTorrentItemText(item, column);
	}
	else if (grabItem->second.type() == download_list::http_list_t)
	{
		return wxT("");
	}
	else
	{
		return wxT("");
	}
}
	
wxString TransferManagerList::GetTorrentItemText(long item, long column) const
{
	libtorrent::torrent_handle h;
	download_handles_t::const_iterator torItem = list.find(item);
	if (torItem->first == item)
 		h = torItem->second.torrent_list().handle;

	if (h.is_valid())
	{
		if (column == 0) // name
		{
			std::string str = h.name();
			return wxString(str.c_str(), wxConvUTF8);
		}

		if (column == 1) // size
		{
			//libtorrent::size_type total_size = h.get_torrent_info().total_size();
			//return wxString::Format(wxT("%f"), total_size);
			return wxT("Unknown");
		}

		if (column == 2) // progress
		{
			libtorrent::size_type progress = h.status().total_done;
			return wxString::Format(wxT("%f"), progress);
		}

		if (column == 3) // status
		{
			if (h.is_paused())
			{
				return wxT("Paused");
			}
			else
			{
				libtorrent::torrent_status::state_t status = h.status().state;
				return state_str.Item(status);
			}
		}

		if (column == 4) // download speed
		{
			libtorrent::size_type download_rate = h.status().download_rate;
			return wxString::Format(wxT("%f"), download_rate);
		}

		if (column == 5) // upload speed
		{
			libtorrent::size_type upload_rate = h.status().upload_rate;
			return wxString::Format(wxT("%f"), upload_rate);
		}

		if (column == 6) // ETA
		{
			return wxT("Unknown");
		}

		if (column == 7) // Downloaded
		{
			libtorrent::size_type downloaded = h.status().total_payload_download;
			return wxString::Format(wxT("%f"), downloaded);
		}

		if (column == 8) // Uploaded
		{
			libtorrent::size_type uploaded = h.status().total_payload_upload;
			return wxString::Format(wxT("%f"), uploaded);
		}

		if (column == 9) // Peers
		{
			int connected_peers = h.status().num_connections;
			int total_peers = h.status().list_peers;
			return wxString::Format(wxT("%i (%i)"), connected_peers, total_peers);
		}

		if (column == 10) // Seeds
		{
			int connected_seeds = h.status().num_seeds;
			int total_seeds = h.status().list_seeds;
			return wxString::Format(wxT("%i (%i)"), connected_seeds, total_seeds);
		}
		
		if (column == 11) // num copies
		{
			float num_copies = h.status().distributed_copies;
			return wxString::Format(wxT("%f"), num_copies);
		}
	}
	else
	{
		return wxT("error");
	}
}