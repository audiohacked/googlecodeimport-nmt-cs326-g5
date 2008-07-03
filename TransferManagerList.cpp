#include <wx/wxprec.h>

#ifndef WX_PRECOMP
	#include <wx/wx.h>
#endif

#include <wx/listctrl.h>
#include <wx/progdlg.h>
#include <wx/utils.h>
#include <wx/sysopt.h>

#include <boost/lexical_cast.hpp>

#include "TorrentManager.h"
#include "HttpManager.h"
#include "TransferManagerList.h"

enum column_id_t
{
	LIST_COL_NAME=0,
	LIST_COL_SIZE,
	LIST_COL_PROGRESS,
	LIST_COL_STATUS,
	LIST_COL_DOWNSPEED,
	LIST_COL_UPSPEED,
	LIST_COL_ETA,
	LIST_COL_DOWNSIZE,
	LIST_COL_UPSIZE,
	LIST_COL_PEERS,
	LIST_COL_SEEDS,
	LIST_COL_COPIES,
	LIST_COL_METADATA
};

struct column_t
{
	int id;
	wxString name;
	int width;
	wxString tooltip;
} TorrentCol[] = {
	{ id: LIST_COL_NAME, name: wxT("Name"), width: 60 },
	{ id: LIST_COL_SIZE, name: wxT("Size"), width: 60 },
	{ id: LIST_COL_PROGRESS, name: wxT("Progress"), width: 80 },
	{ id: LIST_COL_STATUS, name: wxT("Status"), width: 70 },
	{ id: LIST_COL_DOWNSPEED, name: wxT("Down Speed"), width: 100 },
	{ id: LIST_COL_UPSPEED, name: wxT("Up Speed"), width: 80 },
	{ id: LIST_COL_ETA, name: wxT("ETA"), width: 45 },
	{ id: LIST_COL_DOWNSIZE, name: wxT("Downloaded"), width: 100 },
	{ id: LIST_COL_UPSIZE, name: wxT("Uploaded"), width: 80 },
	{ id: LIST_COL_PEERS, name: wxT("Peers"), width: 60 },
	{ id: LIST_COL_SEEDS, name: wxT("Seeds"), width: 60 },
	{ id: LIST_COL_COPIES, name: wxT("Copies"), width: 60 },
	{ id: LIST_COL_METADATA, name: wxT("metadata?"), width: 80 }
};

static const wxString state_str[] = {
	wxT("checking queue"),
	wxT("checking files"),
	wxT("connecting"),
	wxT("dl metadata"),
	wxT("downloading"),
	wxT("finished"),
	wxT("seeding"),
	wxT("allocating")
};

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

	for (int i=0; i<sizeof(TorrentCol)/sizeof(column_t); ++i)
	{
		InsertColumn(TorrentCol[i].id, TorrentCol[i].name ,wxLIST_FORMAT_LEFT, TorrentCol[i].width);
	}
}

#ifdef __TORRENT_MANAGER_H
int TransferManagerList::AddTorrentDownload(char const* name, char const* tracker, char const* TorrentHash)
{
	libtorrent::sha1_hash tor_info_hash = boost::lexical_cast<libtorrent::sha1_hash>(TorrentHash);
	SetItemCount(listIndex+1);
	tor = torrentDownloads->AddTorrentHash(name, tracker, tor_info_hash, listIndex);
	listIndex++;

	return wxOK;
}

int TransferManagerList::AddTorrentMagnetDownload(char const* uri)
{
	SetItemCount(listIndex+1);
	tor = torrentDownloads->AddMagnetURI(uri, listIndex);
	listIndex++;

	return wxOK;
}

int TransferManagerList::AddTorrentFileDownload(char const* file)
{
	SetItemCount(listIndex+1);
	tor = torrentDownloads->AddTorrentFile(file, listIndex);
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
	libtorrent::torrent_status s;
	download_handles_t::const_iterator torItem = list.find(item);
	if (torItem->first == item)
	{
		h = torItem->second.torrent_list().handle;
	}

	if (h.is_valid())
	{
		s = h.status();
		switch(column)
		{
			case LIST_COL_NAME:
				return wxString(h.name().c_str(), wxConvUTF8);
				break;

			case LIST_COL_SIZE:
				return wxT("Unknown");
				break;

			case LIST_COL_PROGRESS:
				return wxString::Format(wxT("%f"), s.total_done);
				break;

			case LIST_COL_STATUS:
				if (h.is_paused() && h.is_auto_managed())
				{
					return wxT("Queued");
				}
				else if (h.is_paused() && !h.is_auto_managed())
				{
					return wxT("Paused");
				}
				else
				{
					return state_str[s.state];
				}
				break;

			case LIST_COL_DOWNSPEED:
				return wxString::Format(wxT("%f"), s.download_rate);
				break;

			case LIST_COL_UPSPEED:
				return wxString::Format(wxT("%f"), s.upload_rate);
				break;

			case LIST_COL_ETA:
				return wxT("Unknown");
				break;

			case LIST_COL_DOWNSIZE:
				return wxString::Format(wxT("%f"), s.total_payload_download);
				break;

			case LIST_COL_UPSIZE:
				return wxString::Format(wxT("%f"), s.total_payload_upload);
				break;

			case LIST_COL_PEERS:
				return wxString::Format(wxT("%i (%i)"), s.num_connections, s.list_peers);
				break;

			case LIST_COL_SEEDS:
				return wxString::Format(wxT("%i (%i)"), s.num_seeds, s.list_seeds);
				break;

			case LIST_COL_COPIES:
				return wxString::Format(wxT("%f"), s.distributed_copies);
				break;
				
			case LIST_COL_METADATA:
				if (!h.has_metadata())
				{
					return wxT("no metadata!");
				}
				else if (h.has_metadata())
				{
					return wxT("found metadata!");
				}
				break;
			
			default:
				return wxT("Error");
				break;
		}
	}
	else
	{
		return wxT("Error");
	}
}
