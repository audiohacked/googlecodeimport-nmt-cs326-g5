#include "AppMenu.h"
#include "config.h"
#include "AppEnum.h"

/* constructor for our menu bar, it returns our menu bar object */
DDPSMenu::DDPSMenu() : wxMenuBar()
{
	wxMenu *FileMenu = new wxMenu(); // create the file menu
	wxMenu *ViewMenu = new wxMenu(); // create the view menu
	//wxMenu *GamesMenu = new wxMenu(); // create the games menu
	wxMenu *HelpMenu = new wxMenu(); // create the help menu

	/* add our "options" for the menu;
		first parameter is the Identifier found in enum.h that is for event handling
		second parameter is the viewable text within the menu
		third is the text we see in the status bar of the window
		*/
	FileMenu->Append(MENU_Logout, _T("Logout..."), _T("Logout/Login or Change user.."));
	//FileMenu->Append(MENU_Update, _T("Check for app updates"), _T("Check online for latest version of App"));
	//FileMenu->AppendSeparator(); // add a horizontal separator
	FileMenu->Append(MENU_Settings, _T("Settings"), _T("Configure DDPS Settings"));
	//FileMenu->AppendSeparator();
	FileMenu->Append(MENU_Quit, _T("E&xit\tCtrl-Q"), _T("Exit demo"));

	//ViewMenu->Append(MENU_Mini, _T("Switch to mini mode"), _T("Switch to mini App Mode"));
	//ViewMenu->AppendSeparator();
	//ViewMenu->Append(MENU_Messenger, _T("Messenger"), _T("Open Chat Messenger"));
	//ViewMenu->AppendSeparator();
	ViewMenu->Append(MENU_Bandwidth, _T("Bandwidth monitor"), _T("View Bandwidth Usage/Speed"));
	ViewMenu->AppendSeparator();
	ViewMenu->Append(MENU_Home, _T("Home"), _T("Go to Homepage"));
	ViewMenu->Append(MENU_Community, _T("Community Portal"), _T("View Profile"));
	ViewMenu->Append(MENU_Downloads, _T("Downloads"), _T("View Downloads Manager"));
	//ViewMenu->Append(MENU_Tools, _T("Tools"), _T("View Tools"));

	/*GamesMenu->Append(MENU_Activate, _T("Activate a product..."));
	GamesMenu->Append(MENU_Invite, _T("Invite a Guest..."));
	GamesMenu->Append(MENU_Add, _T("Add a non-s game to My Games list..."));*/

	HelpMenu->Append(MENU_Support, _T("Support"), _T("Technical support"));
	/*HelpMenu->Append(MENU_SystemInfo, _T("System information"));
	HelpMenu->AppendSeparator();
	HelpMenu->Append(MENU_Privacy, _T("Privacy policy"));
	HelpMenu->Append(MENU_Legal, _T("Legal information"));
	HelpMenu->AppendSeparator();*/
	HelpMenu->Append(MENU_About, _T("&About"), _T("About DDPS"));
#ifdef DEVEL_TESTING
	wxMenu *DebugMenu = new wxMenu();
	DebugMenu->Append(MENU_TorrentDownload, wxT("Add Torrent"));
	DebugMenu->Append(MENU_HTTPDownload, wxT("Add HTTP Download"));
#endif

	/* now we actually append the menus to the menubar */
	Append(FileMenu, _T("&File"));
	Append(ViewMenu, _T("&View"));
#ifdef DEVEL_TESTING
	Append(DebugMenu, _T("&Debug"));
#endif
	//Append(GamesMenu, _T("&DigiContent"));
	Append(HelpMenu, _T("&Help"));
}
