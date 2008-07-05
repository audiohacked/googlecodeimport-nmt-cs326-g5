#ifndef __APP_PANEL_H
#define __APP_PANEL_H
	#include <wx/notebook.h>
	#include <wx/panel.h>
	
	#include "BrowserEmbed.h"
	#include "TransferManager.h"

	class DDPSTabbed : public wxNotebook
	{
		public:
			DDPSTabbed(wxWindow *parent, wxWindowID id, const wxPoint &pos, const wxSize &size, long style);
			DDPSBrowser *Home;
			DDPSBrowser *Community;
			TransferManager *Downloads;
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
			void ChatRosterOpen(wxCommandEvent& event);
			DDPSTabbed *tabs;
			
			DECLARE_EVENT_TABLE()
	};

#endif
