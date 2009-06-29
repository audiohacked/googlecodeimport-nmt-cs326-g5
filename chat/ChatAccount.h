#ifndef __CHAT_ACCOUNT_H
#define __CHAT_ACCOUNT_H
	using namespace gloox;
	class ChatAccount : public  PresenceHandler
	{
		public:
			ChatAccount(Client *client)
			{
				j = client;
				client->registerPresenceHandler( this );
			}
			virtual void handlePresence( Stanza *stanza );

		private:
			Client *j;
	};

#endif
