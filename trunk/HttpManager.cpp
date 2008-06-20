#include "HttpManager.h"
#include "common.h"

HttpTransferManager::HttpTransferManager()
{
	
}

HttpTransferManager::~HttpTransferManager()
{
	
}

void HttpTransferManager::AddDownload(wxString url)
{
	DDPS &myApp = ::wxGetApp();
	if (url.empty())
		return;     // user hit cancel

	wxBitmap bmp;
	//if (m_menuTransferDlg->IsChecked(Minimal_Bitmap))
	//	bmp = wxBitmap(www_xpm);

	wxFileOutputStream fos(wxT("downloaded_stuff"));
	wxCurlDownloadDialog dlg(url, &fos,
							wxT("Download dialog title"),
							wxT("Your message goes here...\nNote that the bitmap below can be hidden/customized."),
							bmp,
							myApp.frame,
							GetTransferStyle());
	//dlg.SetVerbose(m_menuFile->IsChecked(Minimal_Verbose));

	if (!dlg.IsOk())
		return;

	wxCurlDialogReturnFlag flag = dlg.RunModal();

	if (flag == wxCDRF_SUCCESS && fos.GetLength() < 10000)
	{
		fos.Close();
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
	ret |= wxCTDS_CAN_PAUSE;
	ret |= wxCTDS_AUTO_CLOSE;

    return ret;
}