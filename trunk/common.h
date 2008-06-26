#ifndef __COMMON_H
#define __COMMON_H
	#include <wx/wxprec.h>
	#ifndef WX_PRECOMP
		#include <wx/wx.h>
	#endif

	#include "AppMain.h"

	class DDPS : public wxApp
	{
		public:
			virtual bool OnInit();
			virtual int OnExit();

			wxString LoginUsername;
			wxString LoginPassword;
		
			FILE *myLogFile;

			DDPSFrame *frame;
	};
	
	std::string wxString_to_stdString( wxString str );
	wxString stdString_to_wxString( std::string str );

	DECLARE_APP(DDPS)
	
#endif
