#include <wx/wxprec.h>

#ifndef WX_PRECOMP
#	include <wx/wx.h>
#endif

#include "AppTaskbar.h"

BEGIN_EVENT_TABLE(DDPSTaskbarIcon, wxTaskBarIcon)
	//EVT_TASKBAR_LEFT_DCLICK(DDPSTaskbarIcon::)
	//EVT_TASKBAR_CLICK(DDPSTaskbarIcon::)
END_EVENT_TABLE()

DDPSTaskbarIcon::DDPSTaskbarIcon()
{
	
}

DDPSTaskbarIcon::~DDPSTaskbarIcon()
{
	
}
