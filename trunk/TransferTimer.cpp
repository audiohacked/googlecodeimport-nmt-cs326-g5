#include <QtGui>

#include "TransferManager.h"
#include "TransferTimer.h"

TransferManagerTimer::TransferManagerTimer(TransferManager *listctrl, QObject *parent) : QTimer(parent)
{
	ctrl = listctrl;
}

void TransferManagerTimer::Notify()
{
	ctrl->update();
}

void TransferManagerTimer::start()
{
	QTimer::start(100);
}
