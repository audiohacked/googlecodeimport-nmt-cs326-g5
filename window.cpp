#include "window.h"
#include "enum.h"

/* our constructor that creates the tabbed interface. 
it inherits from Notebook
*/
wxSeanTabbed::wxSeanTabbed(wxWindow *parent, wxWindowID id,
	const wxPoint& pos, const wxSize& size, long style) :
wxNotebook(parent, id, pos, size, style)
{
	//win = self.makeHomepage(check.netAppHomepage)
	//win = GassTools.ToolsList(self, check.appNetConfig)
	//win = GassGames.GamesList(self, check.appNetConfig)
	//win = GassMedia.MediaList(self, check.appNetConfig)
	//win = self.makeHomepage(check.netAppHomepage, communityTab=True)

	/* holders for each tab */
	wxPanel *Home, *Community, *Games, *Media, *Tools;

	/* Home is the first tab in the interface */
	Home = new wxSeanDummyPanel(this, -1, wxDefaultPosition, wxDefaultSize,
		wxTAB_TRAVERSAL|wxCLIP_CHILDREN|wxNO_BORDER);
	
	#ifdef COMMUNITY_PORTAL		
		/* Community is 2nd tab */
		Community = new wxSeanDummyPanel(this, -1, wxDefaultPosition, wxDefaultSize,
			wxTAB_TRAVERSAL|wxCLIP_CHILDREN|wxNO_BORDER);
	#endif

	/* Games is the third tab */
	Games = new wxSeanDummyPanel(this, -1, wxDefaultPosition, wxDefaultSize,
		wxTAB_TRAVERSAL|wxCLIP_CHILDREN|wxNO_BORDER);
	
	/* AddPage allows to actually add the tab to the Tabbed Interface 
	first field is the panel that holds the widgets for the tab
	second field is the name of the tab in the interface
	*/
	#ifdef BUILTIN_BROWSER
		AddPage(Home, _T("Tab 1"));
	#endif
	#ifdef COMMUNITY_PORTAL
		AddPage(Community, _T("Tab 2"));
	#endif
	AddPage(Games, _T("Tab 3"));
	//AddPage(Media, _T("My Media"));
	//AddPage(Tools, _T("Tools"));
}

/* this method creates the holder panel for the tabbed interface,
 is a subclass of panel */
wxSeanPanel::wxSeanPanel(wxWindow *parent, wxWindowID id, const wxPoint& pos,
	const wxSize& size, long style) : wxPanel(parent, id, pos, size, style)
{
	/* create a tab interface */
	wxSeanTabbed *tabs = new wxSeanTabbed(this, -1, wxDefaultPosition, wxDefaultSize, wxNB_FIXEDWIDTH);

	/* create a sizer to make the tabbed interface fill the whole window */
	wxGridSizer *sizer = new wxGridSizer(1, 0, 0);
	/* add the tab interface to the sizer */
 	sizer->Add(tabs, 0, wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM, 5);
	/* now set the sizer for this panel, so it is viewable
	 and resizeable */
	SetSizer(sizer);	
}

/* the panel that holds the multiline text box */
wxSeanDummyPanel::wxSeanDummyPanel(wxWindow *parent, wxWindowID id, const wxPoint& pos,
	const wxSize& size, long style) : wxPanel(parent, id, pos, size, style)
{
	wxTextCtrl *MainEditBox = new wxTextCtrl(this, TEXT_Main,
	      wxT("Hi!"), wxDefaultPosition, wxDefaultSize,
	      wxTE_MULTILINE | wxTE_RICH , wxDefaultValidator, wxTextCtrlNameStr);

	/* make a sizer so that the text box fills the screen */
	wxGridSizer *sizer = new wxGridSizer(1, 0, 0);
 	sizer->Add(MainEditBox, 0, wxEXPAND, 0);
	SetSizer(sizer);	
}
