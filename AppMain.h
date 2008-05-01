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

	class sApp : public wxApp
	{
		public:
			virtual bool OnInit();
	};

	class sAppTabbed : public wxNotebook
	{
		public:
			sAppTabbed(wxWindow *parent, wxWindowID id, const wxPoint &pos, const wxSize &size, long style);
			sAppBrowser *Home;
			sAppBrowser *Community;

			DECLARE_EVENT_TABLE()
	};
	
	class sAppPanel : public wxPanel
	{
		public:
			sAppPanel(wxWindow *parent, wxWindowID id, const wxPoint &pos, const wxSize &size, long style);

			void GotoNewsTab(wxCommandEvent&);
			void GotoSupport(wxCommandEvent&);
			sAppTabbed *tabs;

			DECLARE_EVENT_TABLE()
	};
	class sAppFrame : public wxFrame
	{
		public:
			sAppFrame(const wxString &title, const wxPoint &pos, const wxSize &size);

			void OnExit( wxCommandEvent &event);
			void AboutBox(wxCommandEvent &event);
			void SettingsDialog(wxCommandEvent &event);
			void GoToSupportPanel(wxCommandEvent &event);

			sAppPanel *panel;
			DECLARE_EVENT_TABLE()
	};

#endif
