#ifndef __BROWSER_EMBED_H
#define __BROWSER_EMBED_H
	#include "config.h"

	#include "wxMozView.h"
	
	class DDPSBrowser : public wxPanel
	{
		public:
			DDPSBrowser(wxWindow *parent, wxWindowID id, const wxPoint &pos, const wxSize &size);
			~DDPSBrowser();
			
			void GotoHomepage(void);
			wxMozView *browser;
			wxString home;
			wxWindow *wParent;
			
		private:
			void OnPrev(wxCommandEvent& event);
			void OnNext(wxCommandEvent& event);
			void OnStop(wxCommandEvent& event);
			void OnRefresh(wxCommandEvent& event);
			void OnHome(wxCommandEvent& event);
			#ifndef __WXMAC__
			void BeforeLoad(wxMozillaBeforeLoadEvent &event);
			#else
			void BeforeLoad(wxWebViewBeforeLoadEvent &event);
			#endif

			DECLARE_EVENT_TABLE()			
	};

#endif


