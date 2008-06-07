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
	#include <wx/aboutdlg.h>
	#include <wx/generic/aboutdlgg.h>
	
	#include "config.h"

	#include "AppMenu.h"
	#include "AppLogin.h"
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
			wxWindow *wParent;

			DECLARE_EVENT_TABLE()
	};
	
	class DDPSPanel : public wxPanel
	{
		public:
			DDPSPanel(wxWindow *parent, wxWindowID id, const wxPoint &pos, const wxSize &size, long style);

			void GotoNewsTab(wxCommandEvent&);
			void GotoSupport(wxCommandEvent&);
			void GotoHomepage(wxCommandEvent& event);
			void GotoCommunity(wxCommandEvent& event);
			void GotoDownloads(wxCommandEvent& event);
			DDPSTabbed *tabs;
			wxWindow *wParent;
			

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
			void GotoHomepage(wxCommandEvent& event);
			void GotoCommunity(wxCommandEvent& event);
			void GotoDownloads(wxCommandEvent& event);
			void Logout(wxCommandEvent& event);

			DDPSMenu *menu;
			DDPSPanel *panel;
			wxWindow *wParent;
			wxString LoginUsername;
			
			DECLARE_EVENT_TABLE()
	};

#endif
