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
	wxTimer::Start(500);
}