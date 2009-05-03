#ifndef __APP_UPDATE_H
#define __APP_UPDATE_H
	/* 
	   THESE ARE THE ONLY REAL MODIFICATION REQUIRED TO INTEGRATE WEBUPDATER
	   IN YOUR PROGRAM USING IT IN THE SIMPLEST WAY (SEE WEBUPDATER DOCS)
	*/

	#include <wx/frame.h>
	#include <wx/string.h>

	// call this in the event handler used to show the wxWebUpdateDlg
	void wxUpdateAndExit(wxFrame *caller, 
						bool savelog,
	     				bool restart,
	     				const wxString &xrc, 	// --xrc option won't be given using wxEmptyString
	         			const wxString &res,	// --res option won't be given using wxEmptyString
	            		const wxString &xml,	// --xml option won't be given using wxEmptyString
						const wxString &uri);	// --uri option won't be given using wxEmptyString

	// to be called in your wxApp::OnInit()
	void wxUpdateWebUpdaterIfRequired();

#endif
