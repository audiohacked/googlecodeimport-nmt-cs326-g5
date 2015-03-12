# Details #

_Use Case Name_  **DesignateFileSponsoredStatus**

_Participating Actors_

Communicates with ContentServer

Initiated by ContentDistributor

_Flow of Events:_

1. ContentDistributor selects a file which is to have it's sponsored status modified.

2. Client opens connection with ContentServer, queries the sponsored status of the selected file.

> 3. ContentServer connects with and queries DBManager

4. ContentDistributor is given the option to modify this status.

> 5. If changed, the new status is committed to the database by ContentServer.

6. Client closes connection to ContentServer.

_Entry Condition_
  * ContentDistributor who initiated the operation has administrator privileges

_Exit Condition_
  * The database is updated
  * The database does not respond
  * ContentDistributor cancels request

_Quality Requirements_
  * A connection must be maintained between the Client and the ContentServer at all times