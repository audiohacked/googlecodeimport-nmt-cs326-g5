#ifndef __APP_TASKBAR_H
#define __APP_TASKBAR_H
	
	#include <wx/taskbar.h>
	
	class DDPSTaskbarIcon : public wxTaskBarIcon
	{
		public:
			DDPSTaskbarIcon();
			~DDPSTaskbarIcon();
			
		DECLARE_EVENT_TABLE();
	};

#endif
