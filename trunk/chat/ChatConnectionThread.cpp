#include <QtGui>
#include "ChatConnection.h"
#include "ChatConnectionThread.h"
ChatConnThread::ChatConnThread(QObject *parent) : QThread(parent)
{
	server = new ChatConn();
}

void ChatConnThread::run()
{
	server->FetchConnection()->connect( true );
}
