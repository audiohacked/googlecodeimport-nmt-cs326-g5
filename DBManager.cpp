#include <QtSql>
#include "DBManager.h"

DBManager::DBManager(QString dsn, QString un, QString pw)
{
	db = new QSqlDatabase;
	db->addDatabase("QMYSQL");
	db->setHostName();
	db->setDatabaseName();
	db->setUserNmae(un);
	db->setPassword(pw);
}

DBManager::~DBManager()
{
	if (db.isOpen())
	{
		db->close();
		delete db;
		db = NULL;
	}
}

bool DBManager::reportFileDownload(QString fileName)		// public method used by clients to report a completed download
{
	QSqlQuery query(db);
	query.prepare("CALL find_file_by_name(" + fileName + ");");
	query.exec();
	if (query.first())
	{
		int file_id = query.value(0).toInt();
		int download_count = query.value(1).toInt();
	}
		
	//fid now contains file id of the download
	//execute insert procedure
	query.prepare("CALL report_file_download(" + file_id + ");");
	query.exec();

	return true;
}
bool DBManager::reportFileUpload(QString fileName)		// public method used by clients to report a completed upload
{
	QSqlQuery query(db);

	//call the report file info procedure on the server
	query.prepare("CALL find_file_by_name(" + fileName + ");");
	query.exec();
	//get the first result (most likely)
	if (query.first())
	{
		int file_id = query.value(0).toInt();
		int download_count = query.value(1).toInt();
	}
		
	//fid now contains file id of the upload
	//execute insert procedure
	query.prepare("CALL report_file_upload(" + file_id + ");");
	query.exec();

	return true;
}
bool DBManager::designateFileSponsoredStatus(QString fileName, bool isSponsored)	// public method used to update a file record and change it's sponsored status field
{

}
bool DBManager::getFileStatistics(QString fileName)		// public method used to get a specific file's record from the database
{

}
