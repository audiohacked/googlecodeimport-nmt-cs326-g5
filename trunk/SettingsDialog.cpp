#include "SettingsDialog.h"
#include "enum.h"

#define FILENAME "config.ini"
#define BUFFER "This is the config file"

BEGIN_EVENT_TABLE( SettingsFrame, wxFrame )
	EVT_BUTTON(BUTTON_Accept, SettingsFrame::OnAccept)
	EVT_BUTTON(BUTTON_Cancel, SettingsFrame::OnCancel)
END_EVENT_TABLE()

BEGIN_EVENT_TABLE( SettingsPanel, wxPanel )
	//EVT_BUTTON(BUTTON_Accept, SettingsFrame::OnAccept)
	//EVT_BUTTON(BUTTON_Cancel, SettingsFrame::OnCancel)
END_EVENT_TABLE()

//constructor for thDDPSFramee settings frame
SettingsFrame::SettingsFrame(const wxString &title, const wxPoint &pos, const wxSize &size)
: wxFrame((wxFrame*) NULL, -1, title, pos, size)
{
	SettingsPanel *panel = new SettingsPanel(this, -1, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL|wxNO_BORDER);
	panel->SetFocus();
}

void SettingsFrame::OnAccept(wxCommandEvent& WXUNUSED(event))
{
	SaveSettings();
	Close(true);
}

void SettingsFrame::SaveSettings()
{
    wxTextFile file;
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
    file.Write();
}

void SettingsFrame::OnCancel(wxCommandEvent& WXUNUSED(event))
{
	Close(true);
}

//constructor for the setting panel
SettingsPanel::SettingsPanel(wxWindow *parent, wxWindowID id, const wxPoint &pos,
	const wxSize &size, long style) : wxPanel(parent, id, pos, size, style)
{
	
	wxButton *Accept = new wxButton(this, BUTTON_Accept, wxT("Accept"));
	wxButton *Cancel = new wxButton(this, BUTTON_Cancel, wxT("Cancel"));

	wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer *button_sizer = new wxBoxSizer(wxHORIZONTAL);
	sizer->Add(button_sizer, 0, wxALIGN_BOTTOM, 5);
	button_sizer->Add(Accept, 0, wxALL, 10);
	button_sizer->Add(Cancel, 0, wxALL, 10);
	SetSizer(sizer);
	sizer->SetSizeHints(this);
}
