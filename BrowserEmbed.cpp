#include <wx/wxprec.h>
#ifndef WX_PRECOMP
	#include <wx/wx.h>
#endif

#include <wx/filesys.h>
#include <wx/fs_inet.h>
#include <wx/fs_zip.h>
#include <wx/fs_mem.h>
#include <wx/url.h>

#include "AppEnum.h"
#include "AppMain.h"
#include "BrowserEmbed.h"

BEGIN_EVENT_TABLE( DDPSBrowser, wxPanel )
	EVT_BUTTON(BROWSER_Next, DDPSBrowser::OnNext)
	EVT_BUTTON(BROWSER_Prev, DDPSBrowser::OnPrev)
	EVT_BUTTON(BROWSER_Stop, DDPSBrowser::OnStop)
	EVT_BUTTON(BROWSER_Refresh, DDPSBrowser::OnRefresh)
	EVT_BUTTON(BROWSER_Home, DDPSBrowser::OnHome)
#ifndef __WXMAC__
	EVT_MOZILLA_BEFORE_LOAD(DDPSBrowser::BeforeLoad)
#else
	EVT_WEBVIEW_BEFORE_LOAD(BROWSER_WebView, DDPSBrowser::BeforeLoad)
#endif
END_EVENT_TABLE()

DDPSBrowser::DDPSBrowser(wxWindow *parent, wxWindowID id, const wxPoint &pos, const wxSize &size) 
: wxPanel(parent, id, pos, size)
{
	wParent = parent;
#ifndef __WXMAC__
	browser = new wxMozillaBrowser(this, -1, wxDefaultPosition, wxDefaultSize, wxBORDER);
#else
	browser = new wxWebView(this, BROWSER_WebView, wxDefaultPosition, wxDefaultSize);
	browser->MakeEditable(false);
#endif
	
	wxButton *back, *forward, *refresh, *stop, *home;
	
	back 	= new wxButton(this, BROWSER_Prev, 		wxT("Back"));
	forward = new wxButton(this, BROWSER_Next, 		wxT("Forward"));
	refresh = new wxButton(this, BROWSER_Refresh, 	wxT("Refresh"));
	stop 	= new wxButton(this, BROWSER_Stop, 		wxT("Stop"));
	home 	= new wxButton(this, BROWSER_Home, 		wxT("Home"));
	
	wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer *browser_buttons_sizer = new wxBoxSizer(wxHORIZONTAL);

	browser_buttons_sizer->Add(back, 0, wxALL, 10);
	browser_buttons_sizer->Add(forward, 0, wxALL, 10);
	browser_buttons_sizer->Add(refresh, 0, wxALL, 10);
	browser_buttons_sizer->Add(stop, 0, wxALL, 10);
	browser_buttons_sizer->Add(home, 0, wxALL, 10);

	sizer->Add(browser_buttons_sizer, 0,  wxALIGN_TOP, 5);
	sizer->Add(browser, 1, wxEXPAND|wxALL, 5);
	SetSizer(sizer);
}

DDPSBrowser::~DDPSBrowser()
{
	delete browser;
}


#ifndef __WXMAC__
void DDPSBrowser::BeforeLoad(wxMozillaBeforeLoadEvent &event)
#else
void DDPSBrowser::BeforeLoad(wxWebViewBeforeLoadEvent &event)
#endif
{
	wxURL url(event.GetURL());
	
	if (url.GetScheme() == wxString::FromAscii("ddps"))
	{
		event.Cancel();
		wxLogDebug(wxT("DDPS Protocol Intercepted -- ") + event.GetURL());
		
		if (url.GetServer() == wxString::FromAscii("browser"))
		{
			wxString dest = wxT("http:/")+url.GetPath();
			wxLogDebug(dest);
			browser->LoadURL( dest );
		} 
		else if (url.GetServer() == wxString::FromAscii("torrentDownload"))
		{
			wxGetApp().frame->panel->tabs->Downloads->listDownloads->AddTorrentFileDownload(
				"original.torrent"
			);
			//wxString name = url.GetPath().AfterFirst("/").BeforeFirst("/");
			wxString hash = url.GetPath().AfterFirst(wxChar("/")).BeforeFirst(wxChar("@"));
			wxString tracker = url.GetPath().AfterFirst(wxChar("@"));
			wxLogDebug(wxT("DDPS Protocol Torrent Hash -- ") + hash);
			wxLogDebug(wxT("DDPS Protocol Torrent Tracker -- ") + tracker);
			//wParent->Downloads->listDownloads->AddTorrentDownload( name, tracker, hash );
			event.Cancel();
		}
		else if (url.GetServer() == wxString::FromAscii("httpDownload"))
		{
//http://gentoo.osuosl.org/releases/x86/2008.0_beta2/installcd/install-x86-minimal-2008.0_beta2.iso
			wxString addr = wxT("http:/")+url.GetPath();
			//wxGetApp().frame->panel->tabs->Downloads->listDownloads->httpDownloads->AddDownload( addr );
			event.Cancel();
		}
	}
}

void DDPSBrowser::OnPrev(wxCommandEvent& event)
{
	wxLogDebug(wxT("OnPrev..\n"));
	if (browser->CanGoBack())
	{
		browser->GoBack();		
	}
}
void DDPSBrowser::OnNext(wxCommandEvent& event)
{
	wxLogDebug(wxT("OnNext..\n"));
	if ( browser->CanGoForward() )
	{
		browser->GoForward();
	}
}
void DDPSBrowser::OnStop(wxCommandEvent& event)
{
	wxLogDebug(wxT("OnStop..\n"));
#ifndef __WXMAC__
	if ( browser->IsBusy() )
	{
		browser->Stop();
	}
#else
	browser->Stop();
#endif
}
void DDPSBrowser::OnRefresh(wxCommandEvent& event)
{
	wxLogDebug(wxT("OnRefresh..\n"));
#ifndef __WXMAC__
	if ( !browser->IsBusy() )
	{
		browser->Reload();
	}
#else
	browser->Reload();
#endif
}

void DDPSBrowser::OnHome(wxCommandEvent& event)
{
	wxLogDebug(wxT("OnHome..\n"));
	browser->LoadURL(home);
}

void DDPSBrowser::GotoHomepage(void)
{
	wxLogDebug(wxT("GotoHomepage..\n"));
	browser->LoadURL(home);	
}
