# Details #

_Use case name_  RemoveFile

_Participating Actors_
Initiated by BasicUser
Communicates with ContentServer, DBManager

  1. BasicUser selects a file for deletion.
> 2. Client sends delete request to content server.
> > 3. Content server removes file and any related information, opens a connection to the DBManager and sends a corresponding delete (this may actually be an archival rather than a physical deletion) query for the file's database entries.
> > 4. DBManager completes query, ContentServer reports success to client.

> 5. Client reports success to user.

_Entry condition_
  * BasicUser has rights over the file for deletion or is a ContentDistributor.

_Exit condition_
  * File is successfully deleted by ContentServer
  * File's information is successfully deleted from database by DBManager
  * There is a fatal error and the operation cannot continue

_Quality requirements_
  * The user interface must provide an "are you sure" dialogue to the user

**Activity Diagram**

![http://nmt-cs326-g5.googlecode.com/files/act_removefile.jpeg](http://nmt-cs326-g5.googlecode.com/files/act_removefile.jpeg)