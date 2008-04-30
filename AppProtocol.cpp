#include "AppProtocol.h"

ddpsProtocolHandler::ddpsProtocolHandler(const wxString scheme) : wxFSProtocolHandler(scheme)
{

}

ddpsProtocolHandler::~ddpsProtocolHandler()
{

}

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

	return wxFSProtocolHandler::OpenChannel(after);
}

static wxProtocolHandler* ddpsProtocolHandler::Create(const wxString scheme)
{
	return new ddpsProtocolHandler(scheme);
}
