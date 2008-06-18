#include "ChatConnectionThread.h"

ChatConnThread::ChatConnThread() : wxThread()
{
	Create();
	server = new ChatConn();
	threadConn = server->FetchConnection();
}

void *ChatConnThread::Entry()
{
	server->FetchConnection()->connect( true );
}

void ChatConnThread::OnExit()
{
}
