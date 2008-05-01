#ifndef __APP_MAIN_H
#define __APP_MAIN_H
	#include <wx/wxprec.h>
	#ifndef WX_PRECOMP
		#include <wx/wx.h>
	#endif

	#include <wx/utils.h>
	#include <wx/choicebk.h>

	#include <wx/notebook.h>
	#include <wx/panel.h>
	
	#include "config.h"

	#include "AppMenu.h"
	//#include "AppProtocol.h"
	#include "BrowserEmbed.h"
	#include "TransferManager.h"
	#include "SettingsDialog.h"

	class DDPS : public wxApp
	{
		public:
			virtual bool OnInit();
	};

	class DDPSTabbed : public wxNotebook
	{
		public:
			DDPSTabbed(wxWindow *parent, wxWindowID id, const wxPoint &pos, const wxSize &size, long style);
			DDPSBrowser *Home;
			DDPSBrowser *Community;

			DECLARE_EVENT_TABLE()
	};
	
	class DDPSPanel : public wxPanel
	{
		public:
			DDPSPanel(wxWindow *parent, wxWindowID id, const wxPoint &pos, const wxSize &size, long style);

			void GotoNewsTab(wxCommandEvent&);
			void GotoSupport(wxCommandEvent&);
			DDPSTabbed *tabs;

			DECLARE_EVENT_TABLE()
	};
	class DDPSFrame : public wxFrame
	{
		public:
			DDPSFrame(const wxString &title, const wxPoint &pos, const wxSize &size);

			void OnExit( wxCommandEvent &event);
			void AboutBox(wxCommandEvent &event);
			void SettingsDialog(wxCommandEvent &event);
			void GoToSupportPanel(wxCommandEvent &event);

			DDPSPanel *panel;
			DECLARE_EVENT_TABLE()
	};

#endif