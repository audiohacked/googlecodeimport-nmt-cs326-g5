# Details #

Preconditions: User has requested a HTTP File transfer in which some error has occured.

Actors: Tracker, Basic Content Server

  1. Send error to content distributor.

> 2.  Send error to user.

> 3.  Depending on error ask user to retry.

> 4.  If yes retry transfer.

> 5.  If no:

  1. Ask user to remove file.

> 2. Possibly remove file.