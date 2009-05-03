#include <QtGui>
#include <QtNetwork>

#include "HttpManager.h"

HttpTransferManager::HttpTransferManager(QWidget *parent)
: QWidget(parent)
{
}

HttpTransferManager::~HttpTransferManager()
{	
}

int HttpTransferManager::AddDownload(QString url)
{
	if (url.isEmpty())
		return -1;     // user hit cancel

	QString filename = url.split('/', QString::SkipEmptyParts).last();
	QUrl *dl_url = new QUrl(url);

	QMessageBox::information(this, tr("HttpDownload-HttpTransferManager"), tr("filename: ")+filename+tr(" \turl: ")+url);

	QFile *dl_file = new QFile(filename);
	
	QHttp *dl = new QHttp(dl_url->host(), dl_url->port());
	dl->get(dl_url->path(), dl_file);

	return 0;
}
