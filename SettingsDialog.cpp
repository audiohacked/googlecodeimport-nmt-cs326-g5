#include "SettingsDialog.h"
#include "AppEnum.h"
#include <stdlib.h>

#include "AppMain.h"

#define FILENAME "config.ini"
#define BUFFER "This is the config file"

BEGIN_EVENT_TABLE( SettingsFrame, wxDialog )
	EVT_BUTTON(wxID_OK, SettingsFrame::SaveSettings)
END_EVENT_TABLE()


//constructor for thDDPSFramee settings frame
SettingsFrame::SettingsFrame(wxWindow * parent, wxWindowID id, const wxString & title,
                           const wxPoint & pos, const wxSize & size, long style ) 
: wxDialog(parent, id, title, pos, size)
{
	//define ok and cancel buttons
	wxButton *Ok_Button = new wxButton(this, wxID_OK, wxT("Accept"), wxDefaultPosition, wxDefaultSize);
	wxButton *Cancel_Button = new wxButton(this, wxID_CANCEL, wxT("Cancel"), wxDefaultPosition, wxDefaultSize);
	
	//define download directory label and control
	downloadLocation = new wxTextCtrl(this, 
		TEXT_DownloadLocation, wxGetApp().myConfig->cfg_download_location, wxDefaultPosition, wxDefaultSize);
	wxStaticText* downloadLocationLabel = new wxStaticText ( this, wxID_STATIC,
		wxT("&Download Location:"), wxDefaultPosition, wxDefaultSize, 0 );

	//download/upload speed label and control
	downloadSpeed = new wxSpinCtrl ( this, TEXT_DownloadSpeed,
		wxString::Format(wxT("%d"), wxGetApp().myConfig->cfg_download_speed ),
		wxDefaultPosition, wxSize(60, -1),
		wxSP_ARROW_KEYS, -1, 5000, wxGetApp().myConfig->cfg_download_speed );
	wxStaticText* downloadSpeedLabel = new wxStaticText ( this, wxID_STATIC,
		wxT("&Max Download Speed (KBytes/s):"), wxDefaultPosition, wxDefaultSize, 0 );

	uploadSpeed = new wxSpinCtrl ( this, TEXT_UploadSpeed,
		wxString::Format(wxT("%d"), wxGetApp().myConfig->cfg_upload_speed ),
		wxDefaultPosition, wxSize(60, -1),
		wxSP_ARROW_KEYS, -1, 5000, wxGetApp().myConfig->cfg_upload_speed );
	wxStaticText* uploadSpeedLabel = new wxStaticText ( this, wxID_STATIC,
		wxT("&Max Upload Speed (KBytes/s):"), wxDefaultPosition, wxDefaultSize, 0 );
	
	//number of peers label and control
	numPeers = new wxSpinCtrl ( this, TEXT_NumPeers,
		wxString::Format(wxT("%d"), wxGetApp().myConfig->cfg_max_peers ),
		wxDefaultPosition, wxSize(60, -1),
		wxSP_ARROW_KEYS, -1, 5000, wxGetApp().myConfig->cfg_max_peers );
	wxStaticText* numPeersLabel = new wxStaticText ( this, wxID_STATIC,
		wxT("&Max Number of Peers:"), wxDefaultPosition, wxDefaultSize, 0 );	

	wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer *button_sizer = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer *top_sizer = new wxBoxSizer(wxVERTICAL);
	sizer->Add(top_sizer, 0, wxALIGN_TOP, 5);
	sizer->Add(button_sizer, 0, wxALIGN_BOTTOM, 5);

	button_sizer->Add(Ok_Button, 0, wxALL, 10);
	button_sizer->Add(Cancel_Button, 0, wxALL, 10);

	top_sizer->Add(downloadLocationLabel, 0,wxALIGN_CENTER_VERTICAL|wxALL, 5); 
	top_sizer->Add(downloadLocation, 1, wxEXPAND|wxALL, 5);
	top_sizer->Add(downloadSpeedLabel, 0,wxALIGN_CENTER_VERTICAL|wxALL, 5); 
	top_sizer->Add(downloadSpeed, 1, wxEXPAND|wxALL, 5);
	top_sizer->Add(uploadSpeedLabel, 0,wxALIGN_CENTER_VERTICAL|wxALL, 5); 
	top_sizer->Add(uploadSpeed, 1, wxEXPAND|wxALL, 5);
	top_sizer->Add(numPeersLabel, 0,wxALIGN_CENTER_VERTICAL|wxALL, 5); 
	top_sizer->Add(numPeers, 1, wxEXPAND|wxALL, 5);

	SetSizer(sizer);
	sizer->SetSizeHints(this);
}

void SettingsFrame::SaveSettings(wxCommandEvent& WXUNUSED(event))
{
	wxGetApp().myConfig->cfg_download_location = downloadLocation->GetValue();
	wxGetApp().myConfig->cfg_download_speed = downloadSpeed->GetValue();
	wxGetApp().myConfig->cfg_upload_speed = uploadSpeed->GetValue();
	wxGetApp().myConfig->cfg_max_peers = numPeers->GetValue();
	EndModal(0);
}
