#include "AppUpdate.h"

#include <wx/protocol/http.h>
#include <wx/ffile.h>
 
//[...]
        // progress bar with 100 units ... declared as wxGauge progress;
	progress = new wxGauge(this, ID_Progress, 100, wxDefaultPosition, wxDefaultSize, wxGA_HORIZONTAL);
//[...]
 
bool GetUpdate::DownloadUpdate()
{
	wxHTTP http;
	http.SetTimeout(120);
	#ifdef UPDATEURL
	http.Connect(wxT(UPDATEURL));
	#else
	http.Connect(wxT("updateddps.seancrazy.net"));
	#endif
	wxInputStream *httpStream = http.GetInputStream(_T("/file.exe"));
 
	if (http.GetError() == wxPROTO_NOERR)
	{
		size_t chunks     = 100;
		size_t chunkSize  = httpStream->GetSize() / chunks;
		char *fileContent = new char[chunkSize];
 
		wxFFile file(_T("file.exe"), _T("wb"));
 
		for (size_t i = 0; i <= chunks; i++)
		{
			progress->SetValue(i * 100/chunks);
			httpStream->Read(fileContent, chunkSize);
 
			file.Write(fileContent, httpStream->LastRead());
		}
		file.Flush();
 
		wxDELETE(fileContent);
	}
 
	http.Close();
	wxDELETE(httpStream);
	return true;
}