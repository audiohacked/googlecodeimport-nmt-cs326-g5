# Details #

_Use case name_  **ExTorrentTransferError**

_Participating Actors:_ Tracker, BasicUser

_Flow of events_

  1. Client detects an error with a torrent transfer.

> 2.   Client reports error to BasicUser.

> 3.   Client asks BasicUser to either retry download or to delete torrent file and/or downloaded files.

> 4.   Client deletes files as necessary.

_Entry conditions_

  * BasicUser is downloading torrent and an error occurs.

_Exit conditions_

  * Data is deleted
  * User selects retry download

_Quality requirements_

  * Client must only delete files pertaining to the affected download
  * Minor issues (particularly temporary connection issues) must be dealt with automatically