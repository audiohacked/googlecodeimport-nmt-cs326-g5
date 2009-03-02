#ifndef __COMMON_H
#define __COMMON_H

	#include <wx/string.h>
	#include <string>
#include "AppMain.h"
	std::string wxString_to_stdString( wxString str );
	wxString stdString_to_wxString( std::string str );

#endif
