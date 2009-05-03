#ifndef __TRANSFER_TIMER_H
#define __TRANSFER_TIMER_H

	#include "TransferManager.h"
	
	class TransferManagerTimer : public QTimer
	{
		public:
			TransferManagerTimer(TransferManager *listctrl, QObject *parent);
			void Notify();
			void start();
			TransferManager *ctrl;
	};

#endif
