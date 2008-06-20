#ifndef __HTTP_MANAGER_H
#define __HTTP_MANAGER_H
	#include <wx/wxprec.h>

	#ifndef WX_PRECOMP
		#include <wx/wx.h>
	#endif
	
	#include <wx/wfstream.h>
	
	#include <wx/curl/dialog.h>
	
	class HttpTransferManager
	{
		public:
			HttpTransferManager();
			~HttpTransferManager();
			void AddDownload(wxString url);
			int GetTransferStyle() const;
	};
	
#endif