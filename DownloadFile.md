# Introduction #

A user downloads a file from a generic server.


_Use Case Name_  DownloadFile

_Flow of events:_

1. User chooses a file to download in file browser

2. Client software queries server to status of file

> 3. Sever responds with status of file

4. Client downloads file if available, using the appropriate protocol

_Entry Condition_
  * The user initiates a download

_Exit Condition_
  * The download completes successfully
  * The download is canceled by the user
  * There is a download error and the download cannot continue

_Quality Requirements_
  * The server and client must communicate within a certain amount of time.

# Sequence Diagram #

![http://nmt-cs326-g5.googlecode.com/files/seq_abstractdownload.jpeg](http://nmt-cs326-g5.googlecode.com/files/seq_abstractdownload.jpeg)