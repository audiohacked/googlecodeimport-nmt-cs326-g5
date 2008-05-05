#ifndef __BROWSER_EMBED_H
#define __BROWSER_EMBED_H
	#include <wx/wxprec.h>
	#ifndef WX_PRECOMP
		#include <wx/wx.h>
	#endif
	
	#include <wx/filesys.h>
	#include <wx/fs_inet.h>
	#include <wx/fs_zip.h>
	#include <wx/fs_mem.h>

	#ifndef __WXMAC__
		#include <wxMoz/wxMozillaBrowser.h>
	#else
		#include <wx/html/webkit.h>
	#endif

	class DDPSBrowser : public wxPanel
	{
		public:
			DDPSBrowser(wxWindow *parent, wxWindowID id, const wxPoint &pos, const wxSize &size);
			#ifndef __WXMAC__
				wxMozillaBrowser *browser;
			#else
				wxWebKitCtrl *browser;
			#endif
			wxString home;
			void GotoHomepage(void);
			
		private:
			void OnPrev(wxCommandEvent& event);
			void OnNext(wxCommandEvent& event);
			void OnStop(wxCommandEvent& event);
			void OnRefresh(wxCommandEvent& event);
			void OnHome(wxCommandEvent& event);
			
			DECLARE_EVENT_TABLE()
			
	};

#endif


