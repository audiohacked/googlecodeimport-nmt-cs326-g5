#ifndef __FRAME_H
#define __FRAME_H

	#include <wx/wxprec.h>

	#ifndef WX_PRECOMP
	#	include <wx/wx.h>
	#endif

	#include <wx/aboutdlg.h> // need to display our AboutBox
	
	/* class for our main window, which in wx terms is called a frame */
	class wxSeanFrame : public wxFrame
	{
		public:
			/* constructor for our main window */
			wxSeanFrame( const wxString &title, const wxPoint &pos, const wxSize &size );
			/* method we call to close the app */
			void OnExit( wxCommandEvent& event );
			/* method we use for pulling up the About Box */
			void AboutBox( wxCommandEvent& event );

			/* this makes event handling possible, the data 
				for this is found in events.h */
			DECLARE_EVENT_TABLE()
	};

#endif