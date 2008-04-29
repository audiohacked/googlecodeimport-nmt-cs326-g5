#include "TransferManager.h"

TransferManager::TransferManager(wxWindow* parent, wxWindowID id,
const wxPoint& pos, const wxSize& size, long style) : wxPanel(parent, id, pos, size, style)
{
     listDownloads = new wxListCtrl(this, -1, wxDefaultPosition, wxDefaultSize, style=wxLC_REPORT);
     
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

void TransferManager::AddTorrentDownload()
{
	
}

void TransferManager::AddHttpDownload()
{

}
