#ifndef __COMMON_H
#define __COMMON_H
	#include <wx/wxprec.h>
	#ifndef WX_PRECOMP
		#include <wx/wx.h>
	#endif

	typedef struct {
		wxString Username;
		wxString Password;
	} LoginInfoData;

	class DDPS : public wxApp
	{
		public:
			virtual bool OnInit();
			virtual int OnExit();
			LoginInfoData myLoginData;
			FILE *myLogFile;
		
	};

	DECLARE_APP(DDPS)
	
#endif
