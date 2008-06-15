#ifndef __CHAT_COMMON_H
#define __CHAT_COMMON_H

	#include <wx/wxprec.h>
	#ifndef WX_PRECOMP
		#include <wx/wx.h>
	#endif
	
	#include <wx/treectrl.h>
	#include <string>
	
	#include <client.h>
	#include <gloox.h>
	using namespace gloox;

	//wxString LoginUsername = wxT("audiohacked");
	//wxString LoginPassword = wxT("deathball");

	enum
	{
		WINDOW_RosterList = wxID_HIGHEST + 1,
		TEXT_MsgText,
		TEXT_ChatText,
		BUTTON_SendMsg
	};

	std::string wx2glooxString( wxString str);
	wxString gloox2wxString( std::string str);

	wxTreeItemId findTreeItem(wxTreeCtrl* pTreeCtrl, const wxTreeItemId& root, const wxString& text);
#endif
