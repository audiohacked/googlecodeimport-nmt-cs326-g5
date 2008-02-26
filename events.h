#include "enum.h" // needed for the MENU_Quit and etc.

/* we have here is the event table used for event handling
	I still have no idea how this works
	*/
BEGIN_EVENT_TABLE( wxSeanFrame, wxFrame )
	EVT_MENU(MENU_Quit, 
		wxSeanFrame::OnExit) /* when we click Quit in the 
							menu system this event closes				
							the window and cleans up */
	EVT_MENU(MENU_About,
	 	wxSeanFrame::AboutBox) /* when we click Help->About_This_App 
								this event opens the about box */
END_EVENT_TABLE()

//BEGIN_EVENT_TABLE( wxSeanMenu, wxMenuBar )
	//EVT_MENU(MENU_Quit, wxSeanFrame::OnExit)
	//EVT_MENU(MENU_About, wxSeanFrame::AboutBox)
	//EVT_MENU(MENU_Update, wxSeanMenu::Update)
	//EVT_MENU(MENU_Messenger, wxSeanMenu::Messenger)
//END_EVENT_TABLE()
