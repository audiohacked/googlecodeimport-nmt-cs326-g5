#ifndef __APP_LOGIN_DLG_H
#define __APP_LOGIN_DLG_H
	#include <wx/wxprec.h>
	#ifndef WX_PRECOMP
		#include <wx/wx.h>
	#endif

	#include <wx/dialog.h>
	#include <wx/textctrl.h>

	//#include "enum.h"

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
		
		DECLARE_EVENT_TABLE()

	};
#endif //__APP_LOGIN_DLG_H
