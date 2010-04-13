IF(${TORRENT_DOWNLOADER} MATCHES ON)
	SET(SRCS ${SRCS} 
		downloader/TorrentAlertTimer.cpp
#		downloader/TorrentBencode.cpp
		downloader/TorrentManager.cpp
		downloader/TorrentProperties.cpp
		downloader/TransferManagerDataTor.cpp
	)
	SET(HDRS ${HDRS} 
		downloader/TorrentAlertTimer.h
#		downloader/TorrentBencode.h
		downloader/TorrentManager.h
		downloader/TorrentProperties.h
		downloader/TransferManagerDataTor.h
	)
ENDIF(${TORRENT_DOWNLOADER} MATCHES ON)