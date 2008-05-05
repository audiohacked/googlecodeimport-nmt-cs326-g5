#ifndef __DB_MANAGER_H
#define __DB_MANAGER_H
        #include "wx/wxprec.h"

       // #ifndef WX_PRECOMP
       //         #include <wx/wx.h>
       // #endif
        
        #include "wx/db.h"
        #include "wx/dbtable.h"
              
        class DBManager
        {
                private:
                        wxDbConnectInf *DbConnectInfo;    // DB connection information
			wxDb *db;    // Database connection
		public:
			//The DBManager requires an active ODBC connection to the database, which is set up outside of this program.
			DBManager(wxString dsn, wxString un, wxString pw);
			bool reportFileDownload(wxString fileName);		// public method used by clients to report a completed download
			bool reportFileUpload(wxString fileName);		// public method used by clients to report a completed upload
			bool designateFileSponsoredStatus(wxString fileName, bool isSponsored);	// public method used to update a file's sponsored status field
			bool getFileStatistics(wxString fileName);		// public method used to get a specific file's record from the database

        };
                
#endif

