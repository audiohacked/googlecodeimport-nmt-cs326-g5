#include "AppLogin.h"

#include "enum.h" // needed for the MENU_Quit and etc.

AppLoginDialog::AppLoginDialog( wxWindow * parent, wxWindowID id, const wxString & title,
                           const wxPoint & pos, const wxSize & size, long style ) 
: wxDialog(parent, id, title, pos, size)
{
	
	wxTextCtrl *username = new wxTextCtrl(this, TEXT_Username, wxT(""), wxDefaultPosition, wxDefaultSize);
	wxTextCtrl *password = new wxTextCtrl(this, TEXT_Password, wxT(""), wxDefaultPosition, wxDefaultSize, wxTE_PASSWORD);

	wxButton *Ok_Button = new wxButton(this, wxID_OK, wxT("Login"), wxDefaultPosition, wxDefaultSize);
	wxButton *Cancel_Button = new wxButton(this, wxID_CANCEL, wxT("Cancel"), wxDefaultPosition, wxDefaultSize);

	wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer *button_sizer = new wxBoxSizer(wxHORIZONTAL);

	sizer->Add(username, 1, wxEXPAND|wxALL, 5);
	sizer->Add(password, 1, wxEXPAND|wxALL, 5);
	sizer->Add(button_sizer, 0, wxALIGN_BOTTOM, 5);

	button_sizer->Add(Ok_Button, 0, wxALL, 10);
	button_sizer->Add(Cancel_Button, 0, wxALL, 10);

	SetSizer(sizer);
	sizer->SetSizeHints(this);

}
