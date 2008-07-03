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

#include "TransferManager.h"
#include "TransferTimer.h"

TransferManagerTimer::TransferManagerTimer(TransferManagerList *listctrl) : wxTimer()
{
	ctrl = listctrl;
}

void TransferManagerTimer::Notify()
{
	ctrl->RefreshItems(0, ctrl->listIndex);
	//ctrl->RefreshItem(0);
}

void TransferManagerTimer::start()
{
	wxTimer::Start(100);
}
