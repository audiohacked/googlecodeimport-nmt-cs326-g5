#include "SettingsDialog.h"
#include "AppEnum.h"
#include <stdlib.h>

#include "AppCommon.h"

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
	wxTextCtrl *downloadLocation = new wxTextCtrl(this, 
		TEXT_DownloadLocation, wxGetApp().myConfig->cfg_download_location, wxDefaultPosition, wxDefaultSize);
	wxStaticText* downloadLocationLabel = new wxStaticText ( this, wxID_STATIC,
    	wxT("&Download Location:"), wxDefaultPosition, wxDefaultSize, 0 );

	//download/upload speed label and control
	wxSpinCtrl* downloadSpeed = new wxSpinCtrl ( this, TEXT_DownloadSpeed,
    	wxString::Format(wxT("%i"), wxGetApp().myConfig->cfg_download_speed), wxDefaultPosition, wxSize(60, -1),
    	wxSP_ARROW_KEYS, 0, 120, 25 );
	wxStaticText* downloadSpeedLabel = new wxStaticText ( this, wxID_STATIC,
    	wxT("&Max Download Speed (KBytes/s):"), wxDefaultPosition, wxDefaultSize, 0 );

	wxSpinCtrl* uploadSpeed = new wxSpinCtrl ( this, TEXT_UploadSpeed,
    	wxString::Format(wxT("%i"), wxGetApp().myConfig->cfg_upload_speed), wxDefaultPosition, wxSize(60, -1),
    	wxSP_ARROW_KEYS, 0, 120, 25 );
	wxStaticText* uploadSpeedLabel = new wxStaticText ( this, wxID_STATIC,
    	wxT("&Max Upload Speed (KBytes/s):"), wxDefaultPosition, wxDefaultSize, 0 );
	
	//number of peers label and control
	wxSpinCtrl* numPeers = new wxSpinCtrl ( this, TEXT_NumPeers,
    	wxString::Format(wxT("%i"), wxGetApp().myConfig->cfg_max_peers), wxDefaultPosition, wxSize(60, -1),
    	wxSP_ARROW_KEYS, 0, 120, 25 );
	wxStaticText* numPeersLabel = new wxStaticText ( this, wxID_STATIC,
    	wxT("&Max Number of Peers:"), wxDefaultPosition, wxDefaultSize, 0 );	

	wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer *button_sizer = new wxBoxSizer(wxHORIZONTAL);
	wxBoxSizer *top_sizer = new wxBoxSizer(wxVERTICAL);
	sizer->Add(top_sizer, 0, wxALIGN_TOP, 5);
	sizer->Add(button_sizer, 0, wxALIGN_BOTTOM, 5);
	
	button_sizer->Add(Ok_Button, 0, wxALL, 10);
	button_sizer->Add(Cancel_Button, 0, wxALL, 10);
	
	//DDPS &myApp = ::wxGetApp();
	//wxStaticText *UsernameLabel = new wxStaticText( this, wxID_STATIC, myApp.myLoginData->Username, wxDefaultPosition, wxDefaultSize, 0);
	//wxStaticText *PasswordLabel = new wxStaticText( this, wxID_STATIC, myApp.myLoginData->Password, wxDefaultPosition, wxDefaultSize, 0); 
	//top_sizer->Add(UsernameLabel, 0, wxALL, 5);
	//top_sizer->Add(PasswordLabel, 0, wxALL, 5);
	
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
    wxTextFile file;
    wxString tmpString;
    wxTextCtrl* downloadLoc = (wxTextCtrl*) FindWindow(TEXT_DownloadLocation);
    wxSpinCtrl* downloadSpd = (wxSpinCtrl*) FindWindow(TEXT_DownloadSpeed); 
    wxSpinCtrl* uploadSpd = (wxSpinCtrl*) FindWindow(TEXT_UploadSpeed); 
    wxSpinCtrl* numPeers = (wxSpinCtrl*) FindWindow(TEXT_NumPeers); 


	wxGetApp().myConfig->cfg_download_location = downloadLoc->GetValue();
	wxGetApp().myConfig->cfg_download_speed = downloadSpd->GetValue();
	wxGetApp().myConfig->cfg_upload_speed = uploadSpd->GetValue();
	wxGetApp().myConfig->cfg_max_peers = numPeers->GetValue();
    EndModal(0);
}
