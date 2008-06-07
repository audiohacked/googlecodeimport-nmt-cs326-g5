#include "AppLogin.h"

#include "enum.h" // needed for the MENU_Quit and etc.

BEGIN_EVENT_TABLE( AppLoginDialog, wxDialog )
	EVT_BUTTON(wxID_CANCEL, AppLoginDialog::Cancel)
	EVT_BUTTON(wxID_OK, AppLoginDialog::CheckLogin)
END_EVENT_TABLE()

AppLoginDialog::AppLoginDialog( wxWindow * parent, wxWindowID id, const wxString & title,
                           const wxPoint & pos, const wxSize & size, long style ) 
: wxDialog(parent, id, title, pos, size)
{
	
	username = new wxTextCtrl(this, TEXT_Username, wxT(""), wxDefaultPosition, wxDefaultSize);
	password = new wxTextCtrl(this, TEXT_Password, wxT(""), wxDefaultPosition, wxDefaultSize, wxTE_PASSWORD);

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

void AppLoginDialog::Cancel(wxCommandEvent& event)
{
	int answer = wxMessageBox(wxString::FromAscii("Quit program?"), 
							wxString::FromAscii("Confirm"),
                            wxYES_NO, this);
  	if (answer == wxYES)
    	EndModal(0);
	
}

void AppLoginDialog::CheckLogin(wxCommandEvent& event)
{
	int answer = 0;

	// check for valid user login
	if (username->GetValue() == wxString::FromAscii("ddps")) {
		if (password->GetValue() == wxString::FromAscii("letmein")) {
			answer = 1;
		}
		else
		{
			answer = 0;
		}
	}
	else
	{
		answer = 0;
	}


	if (answer == 1)
	{
		//wxMessageBox(wxString::FromAscii("Login Success!"), wxString::FromAscii("Login Outcome?"), wxOK, this);
		event.Skip();
	}
	else if (answer == 0)
	{
		wxMessageBox(wxString::FromAscii("Incorrect Login!"), wxString::FromAscii("Login Outcome?"), wxOK, this);
	}
	else
	{
		wxMessageBox(wxString::FromAscii("Error!"),wxString::FromAscii("Bad message"), wxOK, this);
		EndModal(0);
	}
}
