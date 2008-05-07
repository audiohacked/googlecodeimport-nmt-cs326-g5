#include "TransferManager.h"

TransferManager::TransferManager(wxWindow* parent, wxWindowID id,
const wxPoint& pos, const wxSize& size, long style) : wxPanel(parent, id, pos, size, style)
{
	listDownloads = new wxListCtrl(this, -1, wxDefaultPosition, wxDefaultSize, style=wxLC_REPORT);

	#ifdef __TORRENT_MANAGER_H
	torrentDownloads = new TorrentTransferManager();
	#endif

	#ifdef __HTTP_MANAGER_H
	httpDownloads = new HttpTransferManager();
	#endif 
	
	listDownloads->InsertColumn(0, wxT("Name"));
	listDownloads->InsertColumn(1, wxT("Size"));
	listDownloads->InsertColumn(2, wxT("Progress"));
	listDownloads->InsertColumn(3, wxT("Status"));
	listDownloads->InsertColumn(4, wxT("Down Speed"));
	listDownloads->InsertColumn(5, wxT("Up Speed"));
	listDownloads->InsertColumn(6, wxT("ETA"));
	//list->SetColumn(7, wxT("Downloaded"));
	//list->SetColumn(8, wxT("Uploaded"));
	wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);
	sizer->Add(listDownloads, 1, wxEXPAND|wxALL, 5);
	SetSizer(sizer);
	sizer->SetSizeHints(this);
}

#ifdef __TORRENT_MANAGER_H
void TransferManager::AddTorrentDownload(big_number const& TorrentHash)
{
	if (tor = torrentDownloads->AddTorrent(TorrentHash))
	{
		// now add torrent info to list control
		long index = listDownloads->InsertItem();
		listDownloads->SetItem(index, 0, wxString(tor.name())); // name
		listDownloads->SetItem(index, 1, wxString(tor.get_torrent_info().total_size())); // size
		listDownloads->SetItem(index, 2, wxString(tor.status().total_done)); // progress
		listDownloads->SetItem(index, 3, wxString(tor.status().state)); // status
		listDownloads->SetItem(index, 4, wxString(tor.status().download_rate)); // Down Speed
		listDownloads->SetItem(index, 5, wxString(tor.status().upload_rate)); // Up Speed
		listDownloads->SetItem(index, 6, wxString("unknown")); // ETA
	}
}
#endif

#ifdef __HTTP_MANAGER_H
void TransferManager::AddHttpDownload()
{

}
#endif
