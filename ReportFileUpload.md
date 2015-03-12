# Details #

_Use Case Name_  ReportFileUpload

_Participating Actors_
Participated in by BasicUser
Communicates with ContentServer
Communicates with DBManager

_Flow of Events:_

  1. Client completes a BasicUser initiated sponsored file upload, opens connection with ContentServer.

2. ContentServer attempts to open a database connection, if it is not already open, and notifies the Client to send data

> 3. Client sends file upload statistics concerning the recent file transfer (size of file, type of file, description of file, a human readable name of the file, etc.) to ContentServer.

4. ContentServer sends an update/insert command to the DBManager

5. DBManager performs the queries and commits changes to database.

6. DBManager notifies ContentServer of completion, ContentServer notifies client

> 7. Client closes connection to ContentServer.

_Entry Condition_
  * The user completes a sponsored file upload

_Exit Condition_
  * The database is updated
  * The database does not respond

_Quality Requirements_
  * The operation must complete within 30 seconds

**Sequence Diagram**

![http://nmt-cs326-g5.googlecode.com/files/seq_reportfileupload.jpeg](http://nmt-cs326-g5.googlecode.com/files/seq_reportfileupload.jpeg)