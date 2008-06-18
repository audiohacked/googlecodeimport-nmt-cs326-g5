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

	std::string wx2glooxString( wxString str);
	wxString gloox2wxString( std::string str);

	wxTreeItemId findTreeItem(wxTreeCtrl* pTreeCtrl, const wxTreeItemId& root, const wxString& text);
#endif
