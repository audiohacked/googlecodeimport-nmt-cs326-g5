#ifndef __APP_MAIN_H
#define __APP_MAIN_H

	#include <wx/app.h>
	#include <wx/string.h>
	#include "AppFrame.h"
	#include "AppConfig.h"

	class DDPS : public wxApp
	{
		public:
			virtual bool OnInit();
			virtual int OnExit();

			wxString LoginUsername;
			wxString LoginPassword;
		
			FILE *myLogFile;

			DDPSFrame *frame;
			DDPSConfig *myConfig;
	};
	
	DECLARE_APP(DDPS)

#endif