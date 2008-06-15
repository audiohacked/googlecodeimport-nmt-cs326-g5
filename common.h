#ifndef __COMMON_H
#define __COMMON_H
	#include <wx/wxprec.h>
	#ifndef WX_PRECOMP
		#include <wx/wx.h>
	#endif

	#include "ChatConnectionThread.h"
	#include "ChatRoster.h"
	#include "ChatMessage.h"

	typedef struct {
		wxString Username;
		wxString Password;
	} LoginInfoData;

	class DDPS : public wxApp
	{
		public:
			virtual bool OnInit();
			virtual int OnExit();
			void InitChat();

			LoginInfoData myLoginData;
			FILE *myLogFile;

			ChatConnThread *thread;
			ChatWindowRoster *chat;
			ChatRoster *rosterListener;
			ChatMsgSess *cMsg;
			//ChatAccount *cAccount;
	};

	DECLARE_APP(DDPS)
	
#endif
