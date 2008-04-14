#include "BrowserEmbed.h"

sAppBrowser::sAppBrowser(wxWindow *parent, wxWindowID id, const wxPoint &pos, const wxSize &size) :
	wxPanel(parent, id, pos, size)
{
	browser = new wxMozillaBrowser(this, -1, wxDefaultPosition, wxDefaultSize, wxBORDER);

	wxPanel *buttonPanel = new wxPanel(this, -1, wxDefaultPosition, wxDefaultSize);
	
	wxButton *back, *forward, *refresh, *stop, *home;
	
	back = new wxButton(this, -1, wxT("Back"));
	forward = new wxButton(this, -1, wxT("Forward"));
	refresh = new wxButton(this, -1, wxT("Refresh"));
	stop = new wxButton(this, -1, wxT("Stop"));
	home = new wxButton(this, -1, wxT("Home"));
	
	wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer *browser_buttons_sizer = new wxBoxSizer(wxHORIZONTAL);
	sizer->Add(browser_buttons_sizer, 0,  wxALIGN_TOP, 5);
	sizer->Add(browser, 1, wxEXPAND|wxALL, 5);
	browser_buttons_sizer->Add(back, 0, wxALL, 10);
	browser_buttons_sizer->Add(forward, 0, wxALL, 10);
	browser_buttons_sizer->Add(refresh, 0, wxALL, 10);
	browser_buttons_sizer->Add(stop, 0, wxALL, 10);
	browser_buttons_sizer->Add(home, 0, wxALL, 10);
	SetSizer(sizer);
}
