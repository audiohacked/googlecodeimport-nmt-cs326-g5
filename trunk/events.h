#include "enum.h" // needed for the MENU_Quit and etc.

/* we have here is the event table used for event handling
	I still have no idea how this works
	*/
BEGIN_EVENT_TABLE( sAppFrame, wxFrame )
	EVT_MENU(MENU_Quit, 
		sAppFrame::OnExit) /* when we click Quit in the 
							menu system this event closes				
							the window and cleans up */
	EVT_MENU(MENU_About,
	 	sAppFrame::AboutBox) /* when we click Help->About_This_App 
								this event opens the about box */
END_EVENT_TABLE()

BEGIN_EVENT_TABLE( sAppBrowser, wxPanel )
	EVT_BUTTON(BROWSER_Next, sAppBrowser::OnNext)
	EVT_BUTTON(BROWSER_Prev, sAppBrowser::OnPrev)
	EVT_BUTTON(BROWSER_Stop, sAppBrowser::OnStop)
	EVT_BUTTON(BROWSER_Refresh, sAppBrowser::OnRefresh)
	EVT_BUTTON(BROWSER_Home, sAppBrowser::OnHome)
END_EVENT_TABLE()

/*BEGIN_EVENT_TABLE( sAppPanel, wxPanel )
	EVT_BUTTON(TABB_News, sAppPanel::OnNewsButton)
	EVT_BUTTON(TABB_Settings, sAppPanel::OnSettingsButton)
	EVT_BUTTON(TABB_Support, sAppPanel::OnSupportButton)
	//EVT_BUTTON(TABB_IM, sAppPanel::OnIMButton)
END_EVENT_TABLE()*/

//BEGIN_EVENT_TABLE( wxSeanMenu, wxMenuBar )
	//EVT_MENU(MENU_Quit, wxSeanFrame::OnExit)
	//EVT_MENU(MENU_About, wxSeanFrame::AboutBox)
	//EVT_MENU(MENU_Update, wxSeanMenu::Update)
	//EVT_MENU(MENU_Messenger, wxSeanMenu::Messenger)
//END_EVENT_TABLE()
