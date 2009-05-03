#include <wx/wxprec.h>
#ifndef WX_PRECOMP
	#include <wx/wx.h>
#endif
#include <wx/textfile.h>
#include <wx/filename.h>

#include "AppUpdate.h"

/* 
   THESE ARE THE ONLY REAL MODIFICATION REQUIRED TO INTEGRATE WEBUPDATER
   IN YOUR PROGRAM USING IT IN THE SIMPLEST WAY (SEE WEBUPDATER DOCS)
*/

// call this in the event handler used to show the wxWebUpdateDlg
void wxUpdateAndExit(wxFrame *caller, 
					bool savelog = FALSE,
     				bool restart = TRUE,
     				const wxString &xrc = wxEmptyString, 	// --xrc option won't be given using wxEmptyString
         			const wxString &res = wxEmptyString,	// --res option won't be given using wxEmptyString
            		const wxString &xml = wxEmptyString,	// --xml option won't be given using wxEmptyString
         			const wxString &uri = wxEmptyString)	// --uri option won't be given using wxEmptyString
{
	wxString opts;
 
 	if (savelog)
  		opts += wxT(" --savelog");
    if (restart)
    	opts += wxT(" --restart");
    if (!xrc.IsEmpty())
     	opts += wxT(" --xrc=") + xrc;
    if (!res.IsEmpty())
    	opts += wxT(" --res=") + res;
 	if (!xml.IsEmpty())
  		opts += wxT(" --xml=") + xml;
 	if (!uri.IsEmpty())
  		opts += wxT(" --uri=") + uri;

#ifdef __WXMSW__
	wxExecute(wxT("DDPS-Updater.exe") + opts);
#elif __WXMAC__
	wxExecute(wxT("./DDPS-Updater.app/Contents/MacOS/DDPS-Updater") + opts);
#else	
	wxExecute(wxT("./DDPS-Updater") + opts);
#endif
	caller->Close(true);
}

// to be called in your wxApp::OnInit()
void wxUpdateWebUpdaterIfRequired()
{
#ifdef __WXMSW__
	wxString newupdater = wxT("_webupdater.exe"), oldupdater = wxT("webupdater.exe");
#elif __WXMAC__
	wxString newupdater = wxT("webupdater.app/Contents/MacOS/_webupdater"), oldupdater = wxT("webupdater.app/Contents/MacOS/webupdater");
#else
	wxString newupdater = wxT("_webupdater"), oldupdater = wxT("webupdater");	
#endif
	if (wxFileName::FileExists(newupdater)) {
		wxRemoveFile(oldupdater);
		wxRenameFile(newupdater, oldupdater);
	}
}
