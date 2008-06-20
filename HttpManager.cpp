#include "HttpManager.h"
#include "common.h"

HttpTransferManager::HttpTransferManager()
{
	
}

HttpTransferManager::~HttpTransferManager()
{
	
}

int HttpTransferManager::AddDownload(wxString url)
{
	DDPS &myApp = ::wxGetApp();
	if (url.empty())
		return wxCANCEL;     // user hit cancel

	wxString filename = url.AfterLast( wxChar('/') );

	wxLogMessage(wxT("filename: ")+filename+wxT(" \turl: ")+url);

	wxBitmap bmp;
	wxFileOutputStream fos( filename );
	wxCurlDownloadDialog dlg(url, &fos,
							filename,
							wxT("Your message goes here...\nNote that the bitmap below can be hidden/customized."),
							bmp,
							myApp.frame,
							GetTransferStyle());
	dlg.SetVerbose(TRUE);

	if (!dlg.IsOk())
		return wxCANCEL;

	wxCurlDialogReturnFlag flag = dlg.RunModal();

	if (flag == wxCDRF_SUCCESS && fos.GetLength() < 10000)
	{
		fos.Close();
		return wxOK;
	}
}

int HttpTransferManager::GetTransferStyle() const
{
    int ret = 0;

	ret |= wxCTDS_ELAPSED_TIME;
	ret |= wxCTDS_ESTIMATED_TIME;
	ret |= wxCTDS_REMAINING_TIME;
	ret |= wxCTDS_SPEED;
	ret |= wxCTDS_SIZE;
	ret |= wxCTDS_URL;
	//ret |= wxCTDS_CONN_SETTINGS_AUTH;
	//ret |= wxCTDS_CONN_SETTINGS_PORT;
	//ret |= wxCTDS_CONN_SETTINGS_PROXY;
	ret |= wxCTDS_CAN_ABORT;
	ret |= wxCTDS_CAN_START;
	//ret |= wxCTDS_CAN_PAUSE;
	//ret |= wxCTDS_AUTO_CLOSE;

    return ret;
}
