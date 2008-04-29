#ifndef __SETTINGS_DIALOG_H
#define __SETTINGS_DIALOG_H

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
	#include <wx/wx.h>
#endif

#include <wx/filesys.h>
//#include <wx/fs_inet.h>
//#include <wx/fs_zip.h>
#include <wx/fs_mem.h>
#include <wx/utils.h>
#include <wx/choicebk.h>
//#include <wx/notebook.h>
#include <wx/panel.h>
#include <wx/ffile.h>
#include <wx/textfile.h>
#include <wx/strconv.h>

class sSettingsFrame : public wxFrame
{
	public:
		sSettingsFrame(const wxString &title, const wxPoint &pos, const wxSize &size);
		void OnAccept( wxCommandEvent &event);
		void OnCancel(wxCommandEvent &event);
		void SaveSettings();
		
		DECLARE_EVENT_TABLE()
};

class sSettingsPanel : public wxPanel
{
	public:
		sSettingsPanel(wxWindow *parent, wxWindowID id, const wxPoint &pos, const wxSize &size, long style);

		DECLARE_EVENT_TABLE()
};

#endif
