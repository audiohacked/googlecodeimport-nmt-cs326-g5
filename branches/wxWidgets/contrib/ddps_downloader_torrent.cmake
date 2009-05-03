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

	#add_definitions(-D_WINSOCK2API_)
	set(shared OFF)
	set(encryption OFF)
	#set(unicode OFF)
	#set(deprecated-functions OFF)
	set(build_tests OFF)
	set(build_examples OFF)

	ADD_SUBDIRECTORY(libtorrent)

	INCLUDE_DIRECTORIES(
		${INCLUDE_DIRECTORIES}
		libtorrent/include
		libtorrent/include/libtorrent
	)
	SET(DDPS_LIBS ${DDPS_LIBS} torrent)
ENDIF(${TORRENT} MATCHES ON)