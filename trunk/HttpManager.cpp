#include <QtGui>
#include <QtNetwork>

#include "HttpManager.h"

HttpTransferManager::HttpTransferManager(QObject *parent)
: QObject(parent)
{	
}

void HttpTransferManager::AddDownload(const QUrl &url)
{
	if (url.scheme() == "http")
	{
		qDebug() << "HttpDownload-HttpTransferManager; Url: " << url.toString();
		http = new HttpDownload;
		http->getFile(url);
	}
	else if (url.scheme() == "ftp")
	{
		qDebug() << "FtpDownload-HttpTransferManager; Url: " << url.toString();
		ftp = new FtpDownload;
		ftp->getFile(url);
	}
	else
	{
		qWarning() << "Invalid Url: scheme";
	}
}

FtpDownload::FtpDownload(QObject *parent)
:QObject(parent)
{
	dl = new QFtp(this);
	dl_file = new QFile(this);

	connect(dl, SIGNAL(done(bool)), this, SLOT(ftpDone(bool)));
}

bool FtpDownload::getFile(const QUrl &url)
{
	if (!url.isValid())
	{
		qCritical() << "Invalid URL";
		return false;
	}
	if (url.scheme() != "ftp")
	{
		qCritical() << "Not an Ftp URL";
		return false;
	}
	if (url.path().isEmpty())
	{
		qCritical() << "URL has no path";
		return false;
	}
	QString localFileName = QFileInfo(url.path()).fileName();
	if (localFileName.isEmpty())
	{
		qCritical() << "No Filename Selected";
		return false;
	}
	dl_file->setFileName(localFileName);
	if (!dl_file->open(QIODevice::WriteOnly))
	{
		qCritical() << "Cannot open" << dl_file->fileName() << "for writing:" << dl_file->errorString();
		return false;
	}
	dl->connectToHost(url.host(), url.port(21));
	dl->login();
	dl->get(url.path(), dl_file);
	dl->close();

	return true;
}

void FtpDownload::ftpDone(bool error)
{
	if (error)
	{
		qDebug() << "Error:" << dl->errorString();
	}
	else
	{
		qDebug() << "File downloaded as" << dl_file->fileName();
	}
	dl_file->close();
	emit done();
}

HttpDownload::HttpDownload(QObject *parent)
:QObject(parent)
{
	dl = new QHttp(this);
	dl_file = new QFile(this);
	connect(dl, SIGNAL(done(bool)), this, SLOT(httpDone(bool)));
	connect(dl, SIGNAL(dataReadProgress(int, int)), this, SLOT(file_progress(int,int)));
}

void HttpDownload::file_progress(int done, int total)
{
	if (total > 0) dl_progress = (done/total);
	else dl_progress = 0.0;
	dl_total = total;
	dl_done = done;
}

bool HttpDownload::getFile(const QUrl &url)
{
	if (!url.isValid())
	{
		qCritical() << "Invalid URL";
		return false;
	}
	if (url.scheme() != "http")
	{
		qCritical() << "Not an Http URL";
		return false;
	}
	if (url.path().isEmpty())
	{
		qCritical() << "URL has no path";
		return false;
	}
	QString localFileName = QFileInfo(url.path()).fileName();
	if (localFileName.isEmpty())
	{
		qCritical() << "No Filename Selected";
		return false;
	}
	dl_file->setFileName(localFileName);
	if (!dl_file->open(QIODevice::WriteOnly))
	{
		qCritical() << "Cannot open" << dl_file->fileName() << "for writing:" << dl_file->errorString();
		return false;
	}
	dl->setHost(url.host(), url.port(80));
	dl->get(url.path(), dl_file);
	dl->close();

	return true;
}
void HttpDownload::httpDone(bool error)
{
	if (error)
	{
		qDebug() << "Error:" << dl->errorString();
	}
	else
	{
		qDebug() << "File downloaded as" << dl_file->fileName();
	}
	dl_file->close();
	emit done();
}