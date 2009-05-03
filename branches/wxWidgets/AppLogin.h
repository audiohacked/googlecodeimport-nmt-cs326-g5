#ifndef __APP_LOGIN_DLG_H
#define __APP_LOGIN_DLG_H
	#include <wx/wxprec.h>
	#ifndef WX_PRECOMP
		#include <wx/wx.h>
	#endif

	#include <wx/dialog.h>
	#include <wx/textctrl.h>
	#include <wx/statline.h>

	//#include AppEnum.h

	class AppLoginDialog : public wxDialog
	{
		public:
			AppLoginDialog(wxWindow * parent, wxWindowID id, const wxString & title,
	              const wxPoint & pos = wxDefaultPosition,
	              const wxSize & size = wxDefaultSize,
	              long style = wxDEFAULT_DIALOG_STYLE); //wxDIALOG_NO_PARENT
			wxTextCtrl * dialogText;
			wxString GetText();
			void Cancel(wxCommandEvent& event);
			void CheckLogin(wxCommandEvent& event);
			wxTextCtrl *username;
			wxTextCtrl *password;
			wxCheckBox *rememberPassword;

		DECLARE_EVENT_TABLE()

	};
	
	class AppLogin
	{
		public:
			AppLogin();
			~AppLogin();
			bool DoLogin();
			bool IsLoginOk() { return m_login_ok; }
			wxString GetUsername() { return user; }
			wxString GetPassword() { return pass; }
			
		private:
			bool m_login_ok;
			wxString user;
			wxString pass;
	};
#endif //__APP_LOGIN_DLG_H
