#include "BrowserEmbed.h"

sAppBrowser::sAppBrowser(wxWindow *parent, wxWindowID id, const wxPoint &pos, const wxSize &size) :
	wxPanel(parent, id, pos, size)
{
/*
	wxFileSystem::AddHandler(new wxInternetFSHandler());
	wxFileSystem::AddHandler(new wxZipFSHandler());
	wxFileSystem::AddHandler(new wxMemoryFSHandler());

	const wxUId proto_id = {(wxUint32)0x8a2bcf71,(wxUint16)0x3f5b,(wxUint16)0x4559,
		{(wxUint8)0x89, (wxUint8)0x0f,(wxUint8)0xf3,(wxUint8)0xc2,(wxUint8)0xe9,(wxUint8)0x8e,
		(wxUint8)0xa7,(wxUint8)0x01}};
	wxRegisterProtocolHandler(wxT("The DDPS protocol handler"), wxT("ddps"), proto_id, &(ddpsProtocolHandler::Create));
*/

	browser = new wxMozillaBrowser(this, -1, wxDefaultPosition, wxDefaultSize, wxBORDER);
	
	wxButton *back, *forward, *refresh, *stop, *home;
	
	back = new wxButton(this, -1, wxT("Back"));
	forward = new wxButton(this, -1, wxT("Forward"));
	refresh = new wxButton(this, -1, wxT("Refresh"));
	stop = new wxButton(this, -1, wxT("Stop"));
	home = new wxButton(this, -1, wxT("Home"));
	
	wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer *browser_buttons_sizer = new wxBoxSizer(wxHORIZONTAL);

	browser_buttons_sizer->Add(back, 0, wxALL, 10);
	browser_buttons_sizer->Add(forward, 0, wxALL, 10);
	browser_buttons_sizer->Add(refresh, 0, wxALL, 10);
	browser_buttons_sizer->Add(stop, 0, wxALL, 10);
	browser_buttons_sizer->Add(home, 0, wxALL, 10);

	sizer->Add(browser_buttons_sizer, 0,  wxALIGN_TOP, 5);
	sizer->Add(browser, 1, wxEXPAND|wxALL, 5);
	SetSizer(sizer);
}

/*
const wxString ddpsProtocolHandler::NewURI(const wxString spec, const wxString base)
{

	if(base.IsEmpty()||spec.StartsWith(wxT("ddps://")))
		return spec;
	
	wxString mutable_base = base;
	const int slash_position = base.Find(wxT('/'), TRUE);

	if(slash_position>7)
		if(!((base[slash_position-1]=='/')&&(base[slash_position-2]==':')))
			mutable_base = base.Mid(0,slash_position);
		else
			mutable_base = base;
	else
		mutable_base = base;

	if (!spec.StartsWith(wxT("/")))
		mutable_base=mutable_base+wxT('/');

	return mutable_base+spec;
}

wxProtocolChannel* ddpsProtocolHandler::OpenChannel(const wxString uri)
{    
	wxString after;
	uri.StartsWith(wxT("ddps://"), &after); 

	return wxProtocolHandler::OpenChannel(after);
}
*/