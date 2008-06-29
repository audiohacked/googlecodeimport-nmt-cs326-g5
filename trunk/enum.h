#ifndef __ENUM_H
#define __ENUM_H

/* this file is used for event handling and other stuff i still dont 
	understand, if anyone figures it out; TELL ME! */

	#include <wx/wxprec.h>

	#ifndef WX_PRECOMP
		#include <wx/wx.h>
	#endif

	enum
	{
		WINDOW_RosterList = wxID_HIGHEST + 1,
		WINDOW_Frame,
		MENU_Logout,
		MENU_Update,
		MENU_Settings,
		MENU_Quit,
		MENU_Mini,
		MENU_Messenger,
		MENU_Bandwidth,
		MENU_Home,
		MENU_Community,
		MENU_Downloads,
		//MENU_Tools,
		MENU_Activate,
		MENU_Invite,
		MENU_Add,
		MENU_Support,
		MENU_SystemInfo,
		MENU_Privacy,
		MENU_Legal,
		MENU_About,
		MENU_TorrentDownload,
		MENU_HTTPDownload,
		MENU_UpdateItem,
		LIST_DownloadManager,
		BROWSER_Next,
		BROWSER_Prev,
		BROWSER_Stop,
		BROWSER_Refresh,
		BROWSER_Home,
		TABB_News,
		TABB_Settings,
		TABB_Support,
		TABPAGE_Browser,
		TABPAGE_Community,
		TABPAGE_Downloads,
		TEXT_Main,
		TEXT_Username,
		TEXT_Password,
		TEXT_DownloadLocation,
		TEXT_DownloadSpeed,
		TEXT_NumPeers,
		TEXT_UploadSpeed,
		TEXT_MsgText,
		TEXT_ChatText,
		BUTTON_CreateAccount,
		BUTTON_FetchPassword,
		BUTTON_Chat,
		BUTTON_Accept,
		BUTTON_Cancel,
		BUTTON_SendMsg
	};

#endif
