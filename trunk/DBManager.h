#ifndef __DB_MANAGER_H
#define __DB_MANAGER_H
	#include <QtGui>
	//#include <QtNetwork>
	#include <QtSql>
	class DBManager
	{
		private:
			QSqlDatabase *DbConnectInfo;    // DB connection information
			QSqlDatabase *db;    // Database connection

		public:
			//The DBManager requires an active ODBC connection to the database, which is set up outside of this program.
			DBManager(QString dsn, QString un, QString pw);
			bool reportFileDownload(QString fileName);		// public method used by clients to report a completed download
			bool reportFileUpload(QString fileName);		// public method used by clients to report a completed upload
			bool designateFileSponsoredStatus(QString fileName, bool isSponsored);	// public method used to update a file's sponsored status field
			bool getFileStatistics(QString fileName);		// public method used to get a specific file's record from the database

	};

#endif
