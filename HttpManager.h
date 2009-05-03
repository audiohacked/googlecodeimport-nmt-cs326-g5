#ifndef __HTTP_MANAGER_H
#define __HTTP_MANAGER_H

#include <QtGui>
#include <QtNetwork>
		
class HttpTransferManager : public QWidget
	{
		public:
			HttpTransferManager(QWidget *parent = 0);
			~HttpTransferManager();
		public slots:
			int AddDownload(QString url);
		private:
			Q_OBJECT
	};
	
#endif
