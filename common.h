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
			LoginInfoData myLoginData;
		
	};

	DECLARE_APP(DDPS)
	
#endif
