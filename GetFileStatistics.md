# Details #

_Use case name_  GetFileStatistics

_Participating Actors_

Initiated by Basic User or ContentServer

Communicates with Content Server, Database

  1. BasicUser queries ContentServer or ContentServer opens a connection with DBManager and queries statistics (number of downloads per day, month, year, or total, popularity rating, sponsored status, etc.) about a given file.
  1. DBManager completes the requested query and serves data to user or server.
  1. Connection between BasicUser/ContentServer is closed.