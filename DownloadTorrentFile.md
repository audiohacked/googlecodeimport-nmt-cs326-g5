# Introduction #

The user queries the server for the .torrent file and downloads it if it is there. Then the user downloads the torrent file.


# Details #
_Use Case Name_    DownloadTorrentFile

_Participating Actors:_

> Initiated by BasicUser

> Communicates with ContentServer, DBServer, Tracker

_Flow of events:_

1. **BasicUser** selects file in file browser portion of program

2. **BasicUser** selects download

3. Client sends out a request to the **ContentServer** for the .torrent file

> 4. **ContentServer** queries **DBServer** as to the status of the file

> 5. **DBServer** returns status of .torrent file to **ContentServer**

> 6. **ContentServer** returns status of .torrent file to **BasicUser**

7. If .torrent file is available, client downloads it from **ContentServer**

8. Client performs checksum on .torrent file to make sure it was transferred successfully

9. Client queries **Tracker** for list of other clients with file or files defined
by .torrent file

  1. . **Tracker** returns list of clients if it exists, error if not

  1. . **Tracker** adds client to list of clients downloading file

12. Client queries other clients to find out who had what pieces of file or files

  1. . Other clients reply and specify what data is available for download

14. Client downloads files piece by piece

_Entry Condition_
  * The user selects a download package in the interface that includes a torrent file

_Exit Condition_
  * Download completes, all files reside on local hard drive. OR
  * Download is cancelled by user. OR
  * There is a fatal download error

_Quality Requirements_
  * All servers will respond within a certain amount of time, determined by server settings.