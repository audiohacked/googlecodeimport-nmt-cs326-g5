#ifndef __TRANSFER_MANAGER_DATA_H
#define __TRANSFER_MANAGER_DATA_H
#include <QtGui>

	class HttpTransferManager;
	class HttpDownload;
	class FtpDownload;

	class HttpDataItem : public QObject, public QTreeWidgetItem
	{
	Q_OBJECT
	public:
		HttpDataItem(HttpTransferManager *tm);
		HttpTransferManager *handle;
		QString name;
	public slots:
		void update_item();
	private:
		int dl_done;
		int dl_total;
	};
#endif
