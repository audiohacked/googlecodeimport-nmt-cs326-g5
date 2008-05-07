#include "SettingsDialog.h"
#include "enum.h"

#define FILENAME "config.ini"
#define BUFFER "This is the config file"

BEGIN_EVENT_TABLE( SettingsFrame, wxDialog )
	//EVT_BUTTON(wxID_OK, SettingsFrame::OnAccept)
	//EVT_BUTTON(wxID_CANCEL, SettingsFrame::OnCancel)
	EVT_BUTTON(wxID_OK, SettingsFrame::SaveSettings)
	//EVT_BUTTON(wxID_CANCEL, SettingsFrame::OnCancel)
END_EVENT_TABLE()

//BEGIN_EVENT_TABLE( SettingsPanel, wxPanel )
//END_EVENT_TABLE()

//constructor for thDDPSFramee settings frame
SettingsFrame::SettingsFrame(wxWindow * parent, wxWindowID id, const wxString & title,
                           const wxPoint & pos, const wxSize & size, long style ) 
: wxDialog(parent, id, title, pos, size)
{
	wxButton *Ok_Button = new wxButton(this, wxID_OK, wxT("Accept"), wxDefaultPosition, wxDefaultSize);
	wxButton *Cancel_Button = new wxButton(this, wxID_CANCEL, wxT("Cancel"), wxDefaultPosition, wxDefaultSize);
	wxTextCtrl *downloadLocation = new wxTextCtrl(this, 
		TEXT_DownloadLocation, wxT(""), wxDefaultPosition, wxDefaultSize);

	wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer *button_sizer = new wxBoxSizer(wxHORIZONTAL);
	sizer->Add(downloadLocation, 1, wxEXPAND|wxALL, 5);
	sizer->Add(button_sizer, 0, wxALIGN_BOTTOM, 5);
	button_sizer->Add(Ok_Button, 0, wxALL, 10);
	button_sizer->Add(Cancel_Button, 0, wxALL, 10);
	SetSizer(sizer);
	sizer->SetSizeHints(this);
}

void SettingsFrame::SaveSettings(wxCommandEvent& WXUNUSED(event))
{
    wxTextFile file;
    wxString downloadLocationS;
    wxTextCtrl* downloadLoc = (wxTextCtrl*) FindWindow(TEXT_DownloadLocation); 

    if (!file.Create(wxT(FILENAME)))
    {
    		file.Open(wxT(FILENAME));
    		file.Clear();
    }
   /*size_t i = 0;
    for (i = 0; i < file.GetLineCount(); i++)
    {
        file[i] = text + file[i];
    }*/
    file.AddLine(wxT("User configuration"));    
    
    if(!downloadLoc->IsEmpty())
    {
    	//downloadLocation = panel->downloadLocation->GetValue();
    	file.AddLine(downloadLoc->GetValue());
	}
    file.Write();
    EndModal(0);
}
