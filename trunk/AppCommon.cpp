#include <wx/wxprec.h>
#ifndef WX_PRECOMP
	#include <wx/wx.h>
#endif

#include "AppCommon.h"

std::string wxString_to_stdString( wxString str )
{
	return std::string(str.mb_str());
}

wxString stdString_to_wxString( std::string str )
{
	return wxString(str.c_str(), wxConvUTF8);
}