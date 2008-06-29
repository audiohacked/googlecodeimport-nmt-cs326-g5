#ifndef __TRANSFER_TIMER_H
#define __TRANSFER_TIMER_H

	#include <wx/wxprec.h>

	#ifndef WX_PRECOMP
		#include <wx/wx.h>
	#endif

	#include <wx/utils.h>
	#include <wx/timer.h>
	
	#include "TransferCommon.h"

	#include <libtorrent/config.hpp>
	#include <libtorrent/entry.hpp>
	#include <libtorrent/session.hpp>
	
	class TransferManagerTimer : public wxTimer
	{
		public:
			TransferManagerTimer(TransferManagerList *listctrl);
			void Notify();
			void start();
			TransferManagerList *ctrl;
	};

#endif
