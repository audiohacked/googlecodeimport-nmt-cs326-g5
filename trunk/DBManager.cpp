#include "DBManager.h"

DBManager::DBManager(wxString dsn, wxString un, wxString pw)
{
	DbConnectInfo = new wxDbConnectInf(0, dsn, un, pw); //create connection info structure
	
	db = new wxDb(DbConnectInfo->GetHenv());  //get SQL environment variable
	
	if (!db->Open(DbConnectInfo))  //attempt to open data source
	{
		printf("Could not open datasource.");
	}
	
}

DBManager::~DBManager()
{
	if (db)
	{
		db->Close();
		delete db;
		db = NULL;
	}
	wxDbCloseConnections();
	DbConnectInfo->FreeHenv();
	delete DbConnectInfo;
}

bool DBManager::reportFileDownload(wxString fileName)		// public method used by clients to report a completed download
{
	wxDBColInf * columnInfo; 
	short numCols = 1;
	//call the report file info procedure on the server
	db->ExecSQL(wxT("CALL find_file_by_name(") + filename + wxT(");"), columnInfo, numCols);
	//get the first result (most likely)
	if (!db->GetNext())
		return false;
	int *fid;
	SDWORD cb;
	if (!db->GetData(1, DB_DATA_TYPE_INTEGER, &fid, 0, &cb))
		return false;
	
	//fid now contains file id of the download
	//execute insert procedure
	if (!db->ExecSQL(wxT("CALL report_file_download(") + *fid + wxT(");"), 0, 0))
		return false;
	return true;
}
bool DBManager::reportFileUpload(wxString fileName)		// public method used by clients to report a completed upload
{
	wxDBColInf * columnInfo; 
	short numCols = 1;
	//call the report file info procedure on the server
	db->ExecSQL(wxT("CALL find_file_by_name(") + filename + wxT(");"), columnInfo, numCols);
	//get the first result (most likely)
	if (!db->GetNext())
		return false;
	int *fid;
	SDWORD cb;
	if (!db->GetData(1, DB_DATA_TYPE_INTEGER, &fid, 0, &cb))
		return false;
	
	//fid now contains file id of the upload
	//execute insert procedure
	if (!db->ExecSQL(wxT("CALL report_file_upload(") + *fid + wxT(");"), 0, 0))
		return false;
	return true;
}
bool DBManager::designateFileSponsoredStatus(wxString fileName, bool isSponsored)	// public method used to update a file record and change it's sponsored status field
{

}
bool DBManager::getFileStatistics(wxString fileName)		// public method used to get a specific file's record from the database
{

}
