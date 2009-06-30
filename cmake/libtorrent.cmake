IF(${TORRENT_DOWNLOADER} MATCHES ON)
	ADD_DEFINITIONS(-DTORRENT_UPNP_LOGGING)
	#ADD_DEFINITIONS(-DTORRENT_BUILDING_SHARED)
	#ADD_DEFINITIONS(-DTORRENT_LINKING_SHARED)

	#ADD_DEFINITIONS(-D_WINSOCK2API_)

	ADD_SUBDIRECTORY(libtorrent)

	LINK_DIRECTORIES( ${LINK_DIRECTORIES} ${Boost_LIBRARY_DIRS} )

	INCLUDE_DIRECTORIES(
		${INCLUDE_DIRECTORIES}
		${Boost_INCLUDE_DIR}
		libtorrent/include
		libtorrent/zlib
		libtorrent/include/libtorrent
		openssl/include
	)
	
	SET(DDPS_LIBS ${DDPS_LIBS} ${Boost_LIBRARIES} torrent-rasterbar)

	set(build_examples OFF CACHE BOOL "" FORCE)
	set(build_tests OFF CACHE BOOL "" FORCE)
	set(deprecated-functions OFF CACHE BOOL "" FORCE)
	set(dht ON CACHE BOOL "" FORCE)
	set(encryption ON CACHE BOOL "" FORCE)
	set(exceptions ON CACHE BOOL "" FORCE)
	set(geoip OFF CACHE BOOL "" FORCE)
	set(pool-allocators ON CACHE BOOL "" FORCE)
	set(resolve-countries OFF CACHE BOOL "" FORCE)
	set(shared ON CACHE BOOL "" FORCE)
	set(tcmalloc OFF CACHE BOOL "" FORCE)
	set(unicode ON CACHE BOOL "" FORCE)
ENDIF(${TORRENT_DOWNLOADER} MATCHES ON)
