#include "browser.h"

sAppBrowser::sAppBrowser(wxWindow *parent, wxWindowID id, const wxPoint &pos, const wxSize &size) :
	wxMozillaBrowser(parent, id, pos, size)
{
	wxMozillaBrowser *browser = new wxMozillaBrowser(this, -1, wxDefaultPosition, wxDefaultSize);

	wxPanel *buttonPanel = new wxPanel(this, -1, wxDefaultPosition, wxDefaultSize);
	
	wxButton *back, *forward, *refresh, *stop, *home;
	
	back = new wxButton(buttonPanel, -1, "Back");
	forward = new wxButton(buttonPanel, -1, "Forward");
	refresh = new wxButton(buttonPanel, -1, "Refresh");
	stop = new wxButton(buttonPanel, -1, "Stop");
	home = new wxButton(buttonPanel, -1, "Home");
	
	wxGridSizer *sizer = new wxGridSizer(1, 0, 0);
	sizer->Add(buttonPanel, 0,  wxEXPAND|wxLEFT|wxRIGHT, 5);
	sizer->Add(browser, 0, wxEXPAND|wxLEFT|wxRIGHT|wxBOTTOM, 5);
	SetSizer(sizer);

}