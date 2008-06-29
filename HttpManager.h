#ifndef __HTTP_MANAGER_H
#define __HTTP_MANAGER_H
	#include <wx/wxprec.h>

	#ifndef WX_PRECOMP
		#include <wx/wx.h>
	#endif
	
	#include <wx/wfstream.h>
	
	#include <wx/curl/dialog.h>

	#include "TransferCommon.h"
		
	class HttpTransferManager
	{
		public:
			HttpTransferManager(download_handles_t *l);
			~HttpTransferManager();
			int AddDownload(wxString url);
			int GetTransferStyle() const;
			download_handles_t *handles;
	};
	
#endif
