#include "AppLogin.h"

#include "enum.h" // needed for the MENU_Quit and etc.

BEGIN_EVENT_TABLE( AppLoginDialog, wxDialog )
	//EVT_BUTTON(wxID_CANCEL, AppLoginDialog::Cancel)
	EVT_BUTTON(wxID_OK, AppLoginDialog::CheckLogin)
END_EVENT_TABLE()

AppLoginDialog::AppLoginDialog( wxWindow * parent, wxWindowID id, const wxString & title,
                           const wxPoint & pos, const wxSize & size, long style ) 
: wxDialog(parent, id, title, pos, size, style)
{
	wxStaticText *usernameText = new wxStaticText(this, -1, wxT("Account name"), wxDefaultPosition, wxDefaultSize, wxALIGN_RIGHT);
	username = new wxTextCtrl(this, TEXT_Username, wxT(""), wxDefaultPosition, wxSize(200,20));
	wxStaticText *passwordText = new wxStaticText(this, -1, wxT("Password"), wxDefaultPosition, wxDefaultSize, wxALIGN_RIGHT);
	password = new wxTextCtrl(this, TEXT_Password, wxT(""), wxDefaultPosition, wxSize(200,20), wxTE_PASSWORD);

	wxCheckBox *rememberPassword = new wxCheckBox(this, -1, wxT("Remember my password"), wxDefaultPosition, wxDefaultSize);
	wxButton *Ok_Button = new wxButton(this, wxID_OK, wxT("Login"), wxDefaultPosition, wxDefaultSize);
	wxButton *Cancel_Button = new wxButton(this, wxID_CANCEL, wxT("Cancel"), wxDefaultPosition, wxDefaultSize);

	wxStaticLine *hlBreak = new wxStaticLine(this, -1, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL);

	wxStaticText *createAccountText = new wxStaticText(this, -1, wxT("Don't have an account?"), wxDefaultPosition, wxDefaultSize);
	wxButton *createAccount = new wxButton(this, BUTTON_CreateAccount, wxT("Create a new account..."), wxDefaultPosition, wxDefaultSize);
	wxStaticText *fetchPasswordText = new wxStaticText(this, -1, wxT("Forgot your login info?"), wxDefaultPosition, wxDefaultSize);
	wxButton *fetchPassword = new wxButton(this, BUTTON_FetchPassword, wxT("Fetch my lost account..."), wxDefaultPosition, wxDefaultSize);

	// sizers and widget placement
	wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer *login = new wxBoxSizer(wxVERTICAL);
	wxFlexGridSizer *loginInput = new wxFlexGridSizer(2);
	wxBoxSizer *button_sizer = new wxBoxSizer(wxHORIZONTAL);
	wxFlexGridSizer *loginOptions = new wxFlexGridSizer(2);

	sizer->Add(login, 0, wxALIGN_CENTER_HORIZONTAL|wxALL|wxLEFT, 20);
	sizer->Add(hlBreak, 0, wxALIGN_CENTER_HORIZONTAL|wxLEFT, 2);
	sizer->Add(loginOptions, 0, wxALIGN_RIGHT|wxALL, 20);

	login->Add(loginInput, 0, wxALIGN_CENTER_HORIZONTAL, 10);
	login->Add(rememberPassword, 0, wxALIGN_CENTER_HORIZONTAL, 10);
	login->Add(button_sizer, 0, wxALIGN_CENTER_HORIZONTAL, 10);

	loginInput->Add(usernameText, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
	loginInput->Add(username, 0, wxALL, 5);
	loginInput->Add(passwordText, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
	loginInput->Add(password, 0, wxALL, 5);

	button_sizer->Add(Ok_Button, 0, wxALL, 5);
	button_sizer->Add(Cancel_Button, 0, wxALL, 5);

	loginOptions->Add(createAccountText, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
	loginOptions->Add(createAccount, 0, wxALL, 5);
	loginOptions->Add(fetchPasswordText, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
	loginOptions->Add(fetchPassword, 0, wxALL, 5);
	
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
	bool answer = false;

	// check for valid user login
	if (username->GetValue() == wxString::FromAscii("ddps")) {
		if (password->GetValue() == wxString::FromAscii("letmein")) {
			answer = true;
		}
		else
		{
			answer = false;
		}
	}
	else
	{
		answer = false;
	}


	if (answer == true)
	{
		int cancelLogin = wxMessageBox(wxString::FromAscii("Logging in!"), wxString::FromAscii("Login Outcome?"), wxOK|wxCANCEL, this);
		if (cancelLogin == wxCANCEL)
		{
			EndModal(0);
		}
		else
		{
			event.Skip();
		}
	}
	else if (answer == false)
	{
		wxMessageBox(wxString::FromAscii("Incorrect Login!"), wxString::FromAscii("Login Outcome?"), wxOK, this);
	}
	else
	{
		wxMessageBox(wxString::FromAscii("Error!"),wxString::FromAscii("Bad message"), wxOK, this);
		EndModal(0);
	}
}
