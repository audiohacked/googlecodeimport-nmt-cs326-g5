#include <wx/wxprec.h>
#ifndef WX_PRECOMP
	#include <wx/wx.h>
#endif
#include <wx/log.h>

#include "AppEnum.h" // needed for the MENU_Quit and etc.
#ifdef CHAT_ENABLED
	#include "ChatCommon.h"
#endif
#include "AppFrame.h"
#include "AppUpdate.h"
#include "AppMain.h"

IMPLEMENT_APP(DDPS)

bool DDPS::OnInit()
{
	wxUpdateWebUpdaterIfRequired();
	
	myConfig  = new DDPSConfig();
	
	#ifdef __DDPS_PROTOCOL_H
		wxFileSystem::AddHandler(new wxInternetFSHandler());
		wxFileSystem::AddHandler(new wxZipFSHandler());
		wxFileSystem::AddHandler(new wxMemoryFSHandler());
	#endif
	
	#ifdef __DDPS_PROTOCOL_H
		const wxUId id = {(wxUint32)0x8a2bcf71,(wxUint16)0x3f5b,(wxUint16)0x4559,
			{(wxUint8)0x89, (wxUint8)0x0f,(wxUint8)0xf3,(wxUint8)0xc2,(wxUint8)0xe9,(wxUint8)0x8e,
			(wxUint8)0xa7,(wxUint8)0x01}};
		wxRegisterProtocolHandler(wxT("The DDPS protocol handler"), wxT("ddps"), id, &(ddpsProtocolHandler::Create));
	#endif
	
	myLogFile = fopen("log.txt", "a+");
	wxLogStderr *LogFile = new wxLogStderr(myLogFile);
	wxLog::SetActiveTarget(LogFile);

	#ifdef __WXMAC__
	//wxApp::s_macPreferencesMenuItemId = PreferencesID;
	#endif
	
	#ifdef __WXMAC__
	//wxApp::s_macHelpMenuTitleName = "Help";
	#endif
		
	frame = new DDPSFrame(_T("DDPSFrame"), wxPoint(50, 50), wxSize(1000,600));
	frame->Show(TRUE);
	SetTopWindow(frame);
		
	return TRUE;
}

int DDPS::OnExit()
{
	myConfig->Save();
	delete wxLog::SetActiveTarget(NULL);
	fclose(myLogFile);

	wxApp::CleanUp();
}
