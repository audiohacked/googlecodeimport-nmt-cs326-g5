#ifndef __HTTP_MANAGER_H
#define __HTTP_MANAGER_H
#include <QtGui>
#include <QtNetwork>
class FtpDownload : public QObject
{
	Q_OBJECT
public:
	FtpDownload(QObject *parent = 0);
	bool getFile(const QUrl &url);
	QFtp *dl;
	QFile *dl_file;
	int dl_done;
	int dl_total;
	int dl_progess;
signals:
	void done();
private slots:
	void ftpDone(bool error);
};

class HttpDownload : public QObject
{
	Q_OBJECT
public:
	HttpDownload(QObject *parent = 0);
	bool getFile(const QUrl &url);
	QHttp *dl;
	QFile *dl_file;
	int dl_done;
	int dl_total;
	float dl_progress;
signals:
	void done();
private slots:
	void httpDone(bool error);
	void file_progress(int done, int total);
};

class HttpTransferManager : public QObject
{
	Q_OBJECT
	public:
		HttpTransferManager(QObject *parent = 0);
		~HttpTransferManager(){};
		HttpDownload *http;
		FtpDownload *ftp;
	public slots:
		void AddDownload(const QUrl &url);
};

#endif
