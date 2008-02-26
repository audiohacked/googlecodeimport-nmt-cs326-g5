#ifndef __MAIN_H
#define __MAIN_H

	#include <wx/wxprec.h> 

	#ifndef WX_PRECOMP
	#	include <wx/wx.h>
	#endif

	/* constructor for our app, it will hold our frames (windows) */
	class wxSeanApp : public wxApp
	{
		public:
			/* method to create our app, we dont called directly
			but through the IMPLEMENT_APP() method
			*/
			virtual bool OnInit();

	};

#endif