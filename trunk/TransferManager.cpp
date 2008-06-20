#include "TransferManager.h"
#include "enum.h"

BEGIN_EVENT_TABLE( TransferManager, wxPanel )
	EVT_CONTEXT_MENU(TransferManager::OnContextMenu)
	EVT_MENU(MENU_TorrentDownload, TransferManager::OnMenuAddTorrent)
	EVT_MENU(MENU_HTTPDownload, TransferManager::OnMenuAddHttpDownlaod)
END_EVENT_TABLE()

TransferManager::TransferManager(wxWindow* parent, wxWindowID id,
const wxPoint& pos, const wxSize& size, long style) : wxPanel(parent, id, pos, size, style)
{
	listDownloads = new wxListCtrl(this, -1, wxDefaultPosition, wxDefaultSize, style=wxLC_REPORT );
	listIndex = 0;

#ifdef __TORRENT_MANAGER_H
	torrentDownloads = new TorrentTransferManager();
#endif

#ifdef __HTTP_MANAGER_H
	httpDownloads = new HttpTransferManager();
#endif 

	//listDownloads->SetColumnWidth(-1, wxLIST_AUTOSIZE_USEHEADER);
	listDownloads->InsertColumn(0, wxT("Name"), wxLIST_FORMAT_LEFT, 80);
	listDownloads->InsertColumn(1, wxT("Size"), wxLIST_FORMAT_LEFT, 80);
	listDownloads->InsertColumn(2, wxT("Progress"), wxLIST_FORMAT_LEFT, 80);
	listDownloads->InsertColumn(3, wxT("Status"), wxLIST_FORMAT_LEFT, 80);
	listDownloads->InsertColumn(4, wxT("Down Speed"), wxLIST_FORMAT_LEFT, 100);
	listDownloads->InsertColumn(5, wxT("Up Speed"), wxLIST_FORMAT_LEFT, 80);
	listDownloads->InsertColumn(6, wxT("ETA"), wxLIST_FORMAT_LEFT, 80);

	//listDownloads->SetColumn(7, wxT("Downloaded"), wxLIST_FORMAT_LEFT, 100);
	//listDownloads->SetColumn(8, wxT("Uploaded"), wxLIST_FORMAT_LEFT, 100);

	wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);
	sizer->Add(listDownloads, 1, wxEXPAND|wxALL, 5);
	SetSizer(sizer);
	sizer->SetSizeHints(this);
}

#ifdef __TORRENT_MANAGER_H
int TransferManager::AddTorrentDownload(char const* tracker, char const* TorrentHash)
{
	tor = torrentDownloads->AddTorrent(tracker, big_number(TorrentHash));
	if (tor.is_valid())
	{
		
		// now add torrent info to list control
		long index = listDownloads->InsertItem(listIndex, wxString(tor.name().c_str(), wxConvUTF8));
		if (index == -1) {
			wxLogMessage(wxT("unsuccessful torrent add: bad insert item"));
			return wxCANCEL;			
		} else {
			listDownloads->SetItem(listIndex, 0, wxString(tor.name().c_str(), wxConvUTF8)); // name
			//listDownloads->SetItem(listIndex, 1, wxString::Format(wxT("%d"), tor.get_torrent_info().total_size())); // size
			listDownloads->SetItem(listIndex, 2, wxString::Format(wxT("%d"), tor.status().total_done)); // progress
			listDownloads->SetItem(listIndex, 3, wxString::Format(wxT("%d"), tor.status().state)); // status
			listDownloads->SetItem(listIndex, 4, wxString::Format(wxT("%f"), tor.status().download_rate)); // Down Speed
			listDownloads->SetItem(listIndex, 5, wxString::Format(wxT("%f"), tor.status().upload_rate)); // Up Speed
			listDownloads->SetItem(listIndex, 6, wxT("unknown")); // ETA
			listIndex++;
			wxLogMessage(wxT("successful torrent add"));
			wxLogMessage(wxT("torrent name: ") +  wxString(tor.name().c_str(), wxConvUTF8));
			return wxMessageBox(wxT("Add Torrent Download"), wxT("Right-Click Add"), wxICON_INFORMATION);			
		}
	} else {
		wxLogMessage(wxT("unsuccessful torrent add: invalid torrent handle"));
		return wxCANCEL;
	}
}
#endif

#ifdef __HTTP_MANAGER_H
int TransferManager::AddHttpDownload(wxString downloadURL)
{
	httpDownloads->AddDownload(downloadURL);
	return wxOK;
}
#endif

void TransferManager::OnContextMenu(wxContextMenuEvent &event)
{
	//wxPoint pos = event.GetPosition();
	wxMenu *contextMenu = new wxMenu();

	contextMenu->Append(MENU_TorrentDownload, wxT("Add Torrent"));
	contextMenu->Append(MENU_HTTPDownload, wxT("Add HTTP Download"));

	PopupMenu(contextMenu);
}

void TransferManager::OnMenuAddTorrent(wxCommandEvent &event)
{
//	int answer = wxMessageBox(wxT("AddTorrent"), wxT("Right-Click Add"), wxICON_INFORMATION);
	int answer = AddTorrentDownload(
		"http://torrents.gentoo.org/tracker.php/announce", 
		"de57802d9ae8a20abf0b151d1e931a65b5a0165b"
	);
	if(answer == wxOK)
		event.Skip();
}

void TransferManager::OnMenuAddHttpDownlaod(wxCommandEvent &event)
{
	//int answer = wxMessageBox(wxT("AddHttpDownload"), wxT("Right-Click Add"), wxICON_INFORMATION);
	int answer = AddHttpDownload(wxT("http://bouncer.gentoo.org/fetch/gentoo-2008.0_beta2-minimal/x86/"));
	if(answer == wxOK)
		event.Skip();
}