#ifndef __MENU_H
#define __MENU_H

	#include <wx/wxprec.h>

	#ifndef WX_PRECOMP
	#	include <wx/wx.h>
	#endif

	/* class of our menu system */
	class wxSeanMenu : public wxMenuBar
	{
		public:
			/* constructor for our menu */
			wxSeanMenu();
	};

#endif