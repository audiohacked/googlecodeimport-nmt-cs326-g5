#ifndef __SETTINGS_DIALOG_H
#define __SETTINGS_DIALOG_H

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
	#include <wx/wx.h>
#endif

#include <wx/filesys.h>
#include <wx/fs_mem.h>
#include <wx/utils.h>
#include <wx/choicebk.h>
#include <wx/panel.h>
#include <wx/ffile.h>
#include <wx/textfile.h>
#include <wx/strconv.h>

class SettingsFrame : public wxDialog
{	
	public:
		SettingsFrame(wxWindow * parent, wxWindowID id, const wxString & title,
	              const wxPoint & pos = wxDefaultPosition,
	              const wxSize & size = wxDefaultSize,
	              long style = wxDEFAULT_DIALOG_STYLE);
		wxTextCtrl *downloadLocation;
		void OnAccept( wxCommandEvent &event);
		void OnCancel(wxCommandEvent &event);
		void SaveSettings(wxCommandEvent& event);

		DECLARE_EVENT_TABLE()
};

/*class SettingsFrame : public wxFrame
{
	public:
		SettingsFrame(const wxString &title, const wxPoint &pos, const wxSize &size);
		SettingsPanel *panel;
		DECLARE_EVENT_TABLE()
};*/

#endif
