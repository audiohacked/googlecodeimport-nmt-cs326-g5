#include <wx/wxprec.h>
#ifndef WX_PRECOMP
	#include <wx/wx.h>
#endif

#include <wx/dialog.h>
#include <wx/string.h>
#include <wx/statline.h>

#include <boost/lexical_cast.hpp>

#include <libtorrent/session.hpp>

#include "TorrentProperties.h"

TorrentProperties::TorrentProperties(wxString const& title, libtorrent::torrent_handle &h)
	: wxDialog(NULL, -1, title, wxDefaultPosition, wxDefaultSize,
	wxDEFAULT_DIALOG_STYLE |
	wxRESIZE_BORDER |
	wxSTAY_ON_TOP
	), i(h.get_torrent_info()), handle(h)
{
	s = h.status();
	
	TorrentInformation();
	TorrentCreator();

	wxStaticLine *static_line = new wxStaticLine(this, -1, wxDefaultPosition, wxSize(100,3), wxLI_HORIZONTAL);

	wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);
	wxFlexGridSizer *tor_info_sizer = new wxFlexGridSizer(2);
	wxFlexGridSizer *tor_creator_sizer = new wxFlexGridSizer(2);

	tor_info_sizer->Add(tor_name_label, 0, wxALL, 0);
	tor_info_sizer->Add(tor_name, 0, wxALL, 0);
	tor_info_sizer->Add(tor_size_label, 0, wxALL, 0);
	tor_info_sizer->Add(tor_size, 0, wxALL, 0);
	tor_info_sizer->Add(tor_tracker_label, 0, wxTOP|wxBOTTOM, 5);
	tor_info_sizer->Add(tor_tracker, 0, wxTOP|wxBOTTOM|wxEXPAND, 10);
	tor_info_sizer->Add(tor_hash_label, 0, wxALL, 0);
	tor_info_sizer->Add(tor_hash, 0, wxALL, 0);
	tor_info_sizer->Add(tor_secure_label, 0, wxALL, 0);
	tor_info_sizer->Add(tor_secure, 0, wxALL, 0);
	tor_info_sizer->Add(tor_comment_label, 0, wxTOP|wxBOTTOM, 5);
	tor_info_sizer->Add(tor_comment, 0, wxTOP|wxBOTTOM|wxEXPAND, 10);
	tor_info_sizer->AddGrowableCol(1);

	tor_creator_sizer->Add(tor_creator_label, 0, wxALL, 0);
	tor_creator_sizer->Add(tor_creator, 0, wxALL, 0);
	tor_creator_sizer->Add(tor_date_label, 0, wxALL, 0);
	tor_creator_sizer->Add(tor_date, 0, wxALL, 0);
	tor_creator_sizer->AddGrowableCol(1);

	sizer->Add(tor_header_info, 0, wxALL, 5);
	sizer->Add(tor_info_sizer, 0, wxALL|wxEXPAND, 5);
	sizer->Add(static_line, 0, wxALL|wxEXPAND, 5);
	sizer->Add(tor_header_creator, 0, wxALL, 5);
	sizer->Add(tor_creator_sizer, 0, wxALL|wxEXPAND, 5);

	SetSizer(sizer);
	sizer->SetSizeHints(this);
}

TorrentProperties::~TorrentProperties()
{
	
}

void TorrentProperties::TorrentInformation()
{
	tor_header_info = new wxStaticText(this, -1, wxT("Torrent Information"));


	tor_name_label = new wxStaticText(this, -1, wxT("Name: "));
	tor_name = new wxStaticText(this, -1, wxString(handle.name().c_str(), wxConvUTF8));


	tor_size_label = new wxStaticText(this, -1, wxT("Size: "));
	tor_size = new wxStaticText(this, -1, wxEmptyString);
	if (i.total_size() > 1000)
		if (i.total_size() > 1000000)
			if (i.total_size() > 1000000000) 
				tor_size->SetLabel(wxString::Format(wxT("%i Files, %d GBytes"), i.num_files(), i.total_size()/1000000000));
			else tor_size->SetLabel(wxString::Format(wxT("%i Files, %d MBytes"), i.num_files(), i.total_size()/1000000));
		else tor_size->SetLabel(wxString::Format(wxT("%i Files, %d KBytes"), i.num_files(), i.total_size()/1000));
	else tor_size->SetLabel(wxString::Format(wxT("%i Files, %d Bytes"), i.num_files(), i.total_size()));


	tor_tracker_label = new wxStaticText(this, -1, wxT("Trackers: "));
	tor_tracker = new wxTextCtrl(this, -1, wxEmptyString,
		wxDefaultPosition, wxDefaultSize,
		wxTE_MULTILINE|wxTE_READONLY|wxTE_DONTWRAP );
	for (std::vector<libtorrent::announce_entry>::const_iterator j=i.trackers().begin(); j < i.trackers().end(); ++j)
	{
		tor_tracker->AppendText(wxString((*j).url.c_str(), wxConvUTF8) + wxT("\n"));
	}


	tor_hash_label = new wxStaticText(this, -1, wxT("Hash: "));
	tor_hash = new wxStaticText(this, -1, 
		wxString(boost::lexical_cast<std::string>(i.info_hash()).c_str(), wxConvUTF8));


	tor_secure_label = new wxStaticText(this, -1, wxT("Secure: "));
	tor_secure = new wxStaticText(this, -1, wxEmptyString);
	if (i.priv())
		tor_secure->SetLabel(wxT("Private Torrent"));
	else
		tor_secure->SetLabel(wxT("Public Torrent"));


	tor_comment_label = new wxStaticText(this, -1, wxT("Comment: "));
	tor_comment = new wxTextCtrl(this, -1, 
		wxString(i.comment().c_str(), wxConvUTF8),
		wxDefaultPosition, wxDefaultSize,
		wxTE_MULTILINE|wxTE_READONLY|wxTE_DONTWRAP);
	
}

//#include <boost/date_time/gregorian/gregorian.hpp>
//#include <boost/date_time/posix_time/posix_time.hpp>
//#include <iostream>
void TorrentProperties::TorrentCreator()
{
	tor_header_creator = new wxStaticText(this, -1, wxT("Created By"));

	tor_creator_label = new wxStaticText(this, -1, wxT("Creator: "));
	tor_creator = new wxStaticText(this, -1, wxT("N/A"));
	//wxString(i.creator().c_str(), wxConvUTF8)
	
	tor_date_label = new wxStaticText(this, -1, wxT("Date: "));
	tor_date = new wxStaticText(this, -1, wxEmptyString);
	//std::string date_str = to_simple_string(i.creation_date().get());
	//tor_date.SetLabel( wxString(date_str.c_str(), wxConvUTF8) );
}
