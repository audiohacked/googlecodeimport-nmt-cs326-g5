#include "frame.h"
#include "menu.h"
#include "window.h"

#include "events.h" // include events table needed for event handling

/* constructor for creating our main window, inherits from wxFrame */
wxSeanFrame::wxSeanFrame( const wxString &title, const wxPoint &pos, const wxSize &size)
: wxFrame( (wxFrame*) NULL, -1, title, pos, size)
{
	
	CreateStatusBar(2); /* create our status bar at the bottom of the window
							parameter is number of "text fields" */
	SetStatusText(wxT("Ready!"), 0); // set status bar text in first field
	
	/* create a new menu */
	wxSeanMenu *menu = new wxSeanMenu();
	SetMenuBar(menu); // set the menu for this window

	/* create the panel that holds the Tabbed Interface */
	wxSeanPanel *panel = new wxSeanPanel(this, -1, wxDefaultPosition, wxDefaultSize,
		wxTAB_TRAVERSAL | wxNO_BORDER);
	panel->SetFocus(); // set focus to the tabbed interface 
}

/* used to cleanly, kinda, shutdown the app */
void wxSeanFrame::OnExit( wxCommandEvent& event )
{
	Close(TRUE);
}

/* this makes the aboutbox, well this is just the event handler */
void wxSeanFrame::AboutBox( wxCommandEvent& WXUNUSED(event) )
{
	wxAboutDialogInfo info; // create a about diglog data object
    info.SetName(_("wxSeanApp"));
    info.SetVersion(_("1.0 Beta"));
    info.SetDescription(_("This program is a Digital Content Distribution and Publishing System ."));
    info.SetCopyright(_("(C) 2008 Sean Nelson <snelson@nmt.edu>"));
	#ifndef WIN32
		wxAboutBox(info); // create the app's about box
	#endif
}
