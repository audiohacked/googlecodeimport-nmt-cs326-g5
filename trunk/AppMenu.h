#ifndef __APP_MENU_H
#define __APP_MENU_H

	#include <wx/wxprec.h>

	#ifndef WX_PRECOMP
	#	include <wx/wx.h>
	#endif

	/* class of our menu system */
	class sAppMenu : public wxMenuBar
	{
		public:
			/* constructor for our menu */
			sAppMenu();
	};

#endif
