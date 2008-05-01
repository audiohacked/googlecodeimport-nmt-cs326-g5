#include "enum.h" // needed for the MENU_Quit and etc.

/* we have here is the event table used for event handling
	I still have no idea how this works
	*/
BEGIN_EVENT_TABLE( DDPSFrame, wxFrame )
	EVT_MENU(MENU_Quit, 
		DDPSFrame::OnExit) /* when we click Quit in the 
							menu system this event closes				
							the window and cleans up */
	EVT_MENU(MENU_About,
	 	DDPSFrame::AboutBox) /* when we click Help->About_This_App 
								this event opens the about box */
END_EVENT_TABLE()

BEGIN_EVENT_TABLE( DDPSBrowser, wxPanel )
	EVT_BUTTON(BROWSER_Next, DDPSBrowser::OnNext)
	EVT_BUTTON(BROWSER_Prev, DDPSBrowser::OnPrev)
	EVT_BUTTON(BROWSER_Stop, DDPSBrowser::OnStop)
	EVT_BUTTON(BROWSER_Refresh, DDPSBrowser::OnRefresh)
	EVT_BUTTON(BROWSER_Home, DDPSBrowser::OnHome)
END_EVENT_TABLE()

/*BEGIN_EVENT_TABLE( DDPSPanel, wxPanel )
	EVT_BUTTON(TABB_News, DDPSPanel::OnNewsButton)
	EVT_BUTTON(TABB_Settings, DDPSPanel::OnSettingsButton)
	EVT_BUTTON(TABB_Support, DDPSPanel::OnSupportButton)
	//EVT_BUTTON(TABB_IM, DDPSPanel::OnIMButton)
END_EVENT_TABLE()*/

//BEGIN_EVENT_TABLE( wxSeanMenu, wxMenuBar )
	//EVT_MENU(MENU_Quit, wxSeanFrame::OnExit)
	//EVT_MENU(MENU_About, wxSeanFrame::AboutBox)
	//EVT_MENU(MENU_Update, wxSeanMenu::Update)
	//EVT_MENU(MENU_Messenger, wxSeanMenu::Messenger)
//END_EVENT_TABLE()
