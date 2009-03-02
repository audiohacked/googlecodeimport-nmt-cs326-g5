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
	#SET(Boost_USE_STATIC_LIBS ON)
	#SET(Boost_USE_MULTITHREAD OFF)
	FIND_PACKAGE(Boost)
	SUBDIRS(libtorrent)
	IF(Boost_FOUND)
		#ADD_DEFINITIONS("-DBOOST_VERSION=${Boost_VERSION}")
		INCLUDE_DIRECTORIES(
			${INCLUDE_DIRECTORIES}
			${Boost_INCLUDE_DIRS})
		LINK_DIRECTORIES(SHARED ${LINK_DIRECTORIES} ${Boost_LIBRARY_DIRS})
	ENDIF(Boost_FOUND)
	INCLUDE_DIRECTORIES(
		${INCLUDE_DIRECTORIES}
		libtorrent/include
		libtorrent/include/libtorrent
	)
	IF(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
		SET(MACOSX_EXTRAS 
			${MACOSX_EXTRAS} 
			libtorrent/libtorrent.dylib
		)
	ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
	SET(DDPS_LIBS ${DDPS_LIBS} torrent)
ENDIF(${TORRENT} MATCHES ON)