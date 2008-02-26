#ifndef __TABBED_H
#define __TABBED_H

	#include <wx/wxprec.h>

	#ifndef WX_PRECOMP
	#	include <wx/wx.h>
	#endif

	#include <wx/notebook.h> // include file for tabbed interface, may not need
	#include <wx/panel.h> // include file for panels to hold widgets

	#include "config.h"

	/* class to create Tabbed Interface */
	class wxSeanTabbed : public wxNotebook
	{
		public:
			/* Constructor? for Tabbed Interface */
			wxSeanTabbed(wxWindow *parent, wxWindowID id,
				const wxPoint& pos, const wxSize& size, long style);
	};

	/* class to hold "frame" for Tabbed Interface */
	class wxSeanPanel : public wxPanel
	{
		public:
			/* Within this constructor we create a new tabbed interface */
			wxSeanPanel(wxWindow *parent, wxWindowID id,
				const wxPoint& pos, const wxSize& size, long style);
	};

	/* class to hold widgets for a tab */
	class wxSeanDummyPanel : public wxPanel
	{
		public:
			/* within this constructor we create a text field */
			wxSeanDummyPanel(wxWindow *parent, wxWindowID id,
				const wxPoint& pos, const wxSize& size, long style);
	};
	
#endif //__TABBED_H