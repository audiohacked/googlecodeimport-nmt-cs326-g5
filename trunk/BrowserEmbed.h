#ifndef __BROWSER_EMBED_H
#define __BROWSER_EMBED_H
	#include <wx/wxprec.h>
	#ifndef WX_PRECOMP
		#include <wx/wx.h>
	#endif
	
	#include <wxmozilla/wxMozilla.h>
	
	class sAppBrowser : public wxPanel
	{
		public:
			sAppBrowser(wxWindow *parent, wxWindowID id, const wxPoint &pos, const wxSize &size);
			wxMozillaBrowser *browser;
	};
	
#endif
