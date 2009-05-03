IF(${TORRENT_DOWNLOADER} MATCHES ON)
	INCLUDE( ${CMAKE_SOURCE_DIR}/cmake/ddps_libtorrent.cmake )
	SET(SRCS ${SRCS} 
		TorrentAlertTimer.cpp
#		TorrentBencode.cpp
		TorrentManager.cpp
		TorrentProperties.cpp
	)
	SET(HDRS ${HDRS} 
		TorrentAlertTimer.h
#		TorrentBencode.h
		TorrentManager.h
		TorrentProperties.h
	)
ENDIF(${TORRENT_DOWNLOADER} MATCHES ON)