#include <wx/wxprec.h>
#ifndef WX_PRECOMP
	#include <wx/wx.h>
#endif

#include <wx/utils.h>
#include <wx/choicebk.h>

#include <wx/notebook.h>
#include <wx/panel.h>
#include <wx/aboutdlg.h>
#include <wx/generic/aboutdlgg.h>
#include <wx/treectrl.h>

#include "config.h"
#include "AppMenu.h"
#include "AppLogin.h"
#include "BrowserEmbed.h"
#include "TransferManager.h"
#include "SettingsDialog.h"
#include "AppConfig.h"

#include "AppMain.h"
#include "AppEnum.h" // needed for the MENU_Quit and etc.
#ifdef CHAT_ENABLED
	#include "ChatCommon.h"
#endif
#include "AppPanel.h"

// Event table for DDPSPanel buttons at the bottom of the program
BEGIN_EVENT_TABLE( DDPSPanel, wxPanel )
	EVT_BUTTON(TABB_News, DDPSPanel::GotoNewsTab)
	EVT_BUTTON(TABB_Support, DDPSPanel::GotoSupport)
	EVT_BUTTON(TABB_Settings, DDPSFrame::SettingsDialog)
#ifdef CHAT_ENABLED
	EVT_BUTTON(BUTTON_Chat, DDPSPanel::ChatRosterOpen)
#endif
END_EVENT_TABLE()

DDPSPanel::DDPSPanel(wxWindow *parent, wxWindowID id, const wxPoint &pos,
	const wxSize &size, long style) : wxPanel(parent, id, pos, size, style)
{
	tabs = new DDPSTabbed(this, -1, wxDefaultPosition, wxDefaultSize, 0);
	
	wxButton *News = new wxButton(this, TABB_News, wxT("News"));
	wxButton *Settings = new wxButton(this, TABB_Settings, wxT("Settings"));
	wxButton *Support = new wxButton(this, TABB_Support, wxT("Support"));
#ifdef CHAT_ENABLED
	wxButton *InstaMessenger = new wxButton(this, BUTTON_Chat, wxT("InstaMessenger"));
#endif
	
	wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer *button_sizer = new wxBoxSizer(wxHORIZONTAL);
	sizer->Add(tabs, 1, wxEXPAND|wxALL, 5);
	sizer->Add(button_sizer, 0, wxALIGN_BOTTOM, 5);
	button_sizer->Add(News, 0, wxALL, 10);
	button_sizer->Add(Settings, 0, wxALL, 10);
	button_sizer->Add(Support, 0, wxALL, 10);
#ifdef CHAT_ENABLED
	button_sizer->Add(InstaMessenger, 0, wxALL, 10);
#endif
	
	SetSizer(sizer);
	sizer->SetSizeHints(this);
}

#ifdef CHAT_ENABLED
void DDPSPanel::ChatRosterOpen(wxCommandEvent& event)
{
	DDPS &myApp = ::wxGetApp();
	if (myApp.frame->chat->IsShown())
	{
		
	}
	else
	{
		myApp.frame->chat->Show(TRUE);
	}
}
#endif

void DDPSPanel::GotoNewsTab(wxCommandEvent& WXUNUSED(event))
{
	#ifdef BUILTIN_BROWSER
		if ( tabs )
		{
			if (tabs->Home->browser)
			{
				#ifdef NEWSPAGE
				tabs->Home->browser->LoadURL(wxT(NEWSPAGE));
				#else
				tabs->Home->browser->LoadURL(wxT("coreyb.homelinux.org/contentmanager/news"));
				#endif
			}
			tabs->ChangeSelection(0);
		}
	#endif
}

void DDPSPanel::GotoSupport(wxCommandEvent& WXUNUSED(event))
{
	#ifdef BUILTIN_BROWSER
		if ( tabs )
		{
			if (tabs->Home->browser)
			{
				#ifdef SUPPORTPAGE
				tabs->Home->browser->LoadURL(wxT(SUPPORTPAGE));
				#else
				tabs->Home->browser->LoadURL(wxT("coreyb.homelinux.org/contentmanager/support"));
				#endif
			}
			tabs->ChangeSelection(0);
		}
	#else
	
	#endif
	
}

void DDPSPanel::GotoHomepage(wxCommandEvent& event)
{
	#ifdef BUILTIN_BROWSER
		tabs->ChangeSelection(0);
	#endif
}

void DDPSPanel::GotoCommunity(wxCommandEvent& event)
{
	#ifdef BUILTIN_BROWSER
		tabs->ChangeSelection(1);
	#elif COMMUNITY_PORTAL
		tabs->ChangeSelection(0);
	#endif
}

void DDPSPanel::GotoDownloads(wxCommandEvent& event)
{
	#ifdef BUILTIN_BROWSER
		tabs->ChangeSelection(2);
	#elif COMMUNITY_PORTAL
		tabs->ChangeSelection(1);
	#else
		tabs->ChangeSelection(0);
	#endif
}

DDPSTabbed::DDPSTabbed(wxWindow *parent, wxWindowID id, const wxPoint &pos,
	 const wxSize &size, long style) : wxNotebook(parent, id, pos, size, style)
{
	#ifdef BUILTIN_BROWSER
		Home = new DDPSBrowser(this, TABPAGE_Browser, 
			wxDefaultPosition, wxDefaultSize);
		#ifdef HOMEPAGE
		Home->home = wxT(HOMEPAGE);
		#else
		Home->home = wxT("coreyb.homelinux.org/contentmanager");
		#endif
		Home->GotoHomepage();
		AddPage(Home, _T("Browser"));
	#endif
	
	#ifdef COMMUNITY_PORTAL
		Community = new DDPSBrowser(this, TABPAGE_Community, 
			wxDefaultPosition, wxDefaultSize);
		#ifdef COMMUNITYPAGE
		Community->home = wxT(COMMUNITYPAGE);
		#else
		Community->home = wxT("coreyb.homelinux.org/contentmanager/community");
		#endif
		Community->GotoHomepage();
		AddPage(Community, _T("Community"));
	#endif

	#ifdef __TRANSFER_MANAGER_H
		Downloads = new TransferManager(this, -1, wxDefaultPosition, 
			wxDefaultSize, wxTAB_TRAVERSAL|wxCLIP_CHILDREN|wxNO_BORDER);
		AddPage(Downloads, _T("Downloads"));
	#endif
}
