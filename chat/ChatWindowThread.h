#ifndef __CHAT_WINDOW_THREAD_H
#define __CHAT_WINDOW_THREAD_H
	class ChatWindowThread : public wxThread
	{
		public:
			ChatWindowThread();
			virtual void *Entry();
			virtual void OnExit();
			ChatConn *server;
						
		private:
			Client *threadConn;
	};

#endif
