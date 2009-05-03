#ifndef __TRANSFER_TIMER_H
#define __TRANSFER_TIMER_H

	#include <wx/timer.h>
	#include "TransferManagerList.h"
	
	class TransferManagerTimer : public wxTimer
	{
		public:
			TransferManagerTimer(TransferManagerList *listctrl);
			void Notify();
			void start();
			TransferManagerList *ctrl;
	};

#endif
