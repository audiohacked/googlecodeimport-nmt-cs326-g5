# Details #
_Use Case Name_  **UploadFile**

_Participating Actors_
Communicates with ContentServer
Initiated by BasicUser or ContentDistributor

_Flow of Events:_

  1. BasicUser or ContentDistributor selects a file to upload.
  1. Client opens connection (if necessary) with the ContentServer.
  1. Client transfers file or files to ContentServer over HTTP.
    1. ContentServer connects to DBManager if not already connected
  1. ContentServer dynamically updates appropriate pages to reflect new content.

_Entry Condition_
  * BasicUser or ContentDistributor who initiated the upload has upload privileges

_Exit Condition_
  * The database is updated
  * The database does not respond

_Quality Requirements_
  * A connection must be maintained between the Client and the ContentServer at all times

**Activity Diagram**

![http://nmt-cs326-g5.googlecode.com/files/act_upload.jpeg](http://nmt-cs326-g5.googlecode.com/files/act_upload.jpeg)