#include "ChatRosterData.h"

ChatContactItemData::ChatContactItemData(wxString contact, JID contact_jid)
{
	jid = contact_jid;
	wx_jid = wxString(contact_jid.full().c_str(), wxConvUTF8);
	name = contact;
	hasWin = false;
	conn = NULL;
	win = NULL;
}

ChatContactItemData::~ChatContactItemData()
{
	hasWin = false;
}

