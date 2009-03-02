IF(${TORRENT} MATCHES ON)
	SET(SRCS ${SRCS} 
		TorrentAlertTimer.cpp
		TorrentBencode.cpp
		TorrentManager.cpp
		TorrentProperties.cpp
	)
	SET(HDRS ${HDRS} 
		TorrentAlertTimer.h
		TorrentBencode.h
		TorrentManager.h
		TorrentProperties.h
	)

	ADD_SUBDIRECTORY(libtorrent)

	INCLUDE_DIRECTORIES(
		${INCLUDE_DIRECTORIES}
		libtorrent/include
		libtorrent/include/libtorrent
	)
	SET(DDPS_LIBS ${DDPS_LIBS} torrent)
ENDIF(${TORRENT} MATCHES ON)