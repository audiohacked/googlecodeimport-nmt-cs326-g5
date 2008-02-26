#include "main.h"
#include "frame.h" /* frame is what we call a window,
 					weird and sometimes confusing */

IMPLEMENT_APP(wxSeanApp) // implements the actual main function of program

bool wxSeanApp::OnInit() // kinda like the main function of our project
{
	/* create a new window for our app */
	wxSeanFrame *frame = new wxSeanFrame(_T("wxSeanApp"), wxPoint(50, 50), wxSize(800,600));
	/* make sure we actually show the app window */
	frame->Show(TRUE);
	/* tells the app that our frame we created is the main/top
	 window for the app */
	SetTopWindow(frame);
	return TRUE;
}