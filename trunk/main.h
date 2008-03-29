#ifndef __MAIN_H
#define __MAIN_H
	#include <wx/wxprec.h>
	#ifndef WX_PRECOMP
		#include <wx/wx.h>
	#endif

	#include <wx/notebook.h>
	#include <wx/panel.h>
	
	#include "config.h"

	class sApp : public wxApp
	{
		public:
			virtual bool OnInit();
	};

	class sAppFrame : public wxFrame
	{
		public:
			sAppFrame(const wxString &title, const wxPoint &pos, 
				const wxSize &size);
			void OnExit( wxCommandEvent &event);
			void AboutBox(wxCommandEvent &event);

			DECLARE_EVENT_TABLE()
	};
	
	class sAppTabbed : public wxNotebook
	{
		public:
			sAppTabbed(wxWindow *parent, wxWindowID id, const wxPoint &pos,
				const wxSize &size, long style);
	};
	
	class sAppPanel : public wxPanel
	{
		public:
			sAppPanel(wxWindow *parent, wxWindowID id, const wxPoint &pos,
				const wxSize &size, long style);
	};
#endif
