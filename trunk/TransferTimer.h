#ifndef __TRANSFER_TIMER_H
#define __TRANSFER_TIMER_H

	#include "TransferManager.h"
	
	class TransferManagerTimer : public QTimer
	{
		Q_OBJECT
		public:
			TransferManagerTimer(TransferManager *listctrl, QObject *parent);
			TransferManager *ctrl;
		public slots:
			void Notify();
		private:
	};


#endif
