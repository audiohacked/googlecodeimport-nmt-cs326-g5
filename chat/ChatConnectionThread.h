#ifndef __CHAT_CONNECTION_THREAD_H
#define __CHAT_CONNECTION_THREAD_H

	#include <QtGui>
	
	#include "ChatConnection.h"

	class ChatConnThread : public QThread
	{
		public:
			ChatConnThread(QObject *parent=0);
			ChatConn *server;
		protected:
			virtual void run();
		private:
			Q_OBJECT
	};

#endif
