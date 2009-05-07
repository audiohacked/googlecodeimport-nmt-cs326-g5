IF(${TORRENT_DOWNLOADER} MATCHES ON)
add_definitions(-DWIN32)
add_definitions(-D_WIN32)
add_definitions(-DWIN32_LEAN_AND_MEAN)
add_definitions(-D_WIN32_WINNT=0x0501)
add_definitions(-DTORRENT_UPNP_LOGGING)

#add_definitions(-DTORRENT_BUILDING_SHARED)
#add_definitions(-DTORRENT_LINKING_SHARED)

#add_definitions(-D_WINSOCK2API_)

ADD_SUBDIRECTORY(libtorrent)

INCLUDE_DIRECTORIES(
	${INCLUDE_DIRECTORIES}
	libtorrent/include
	libtorrent/zlib
	libtorrent/include/libtorrent
	openssl/include
)
SET(DDPS_LIBS ${DDPS_LIBS} torrent-rasterbar)

set(build_examples OFF FORCE)
set(build_tests OFF FORCE)
set(deprecated-functions OFF FORCE)
set(dht ON FORCE)
#set(encryption ON FORCE)
#set(exceptions ON FORCE)
set(geoip OFF FORCE)
#set(pool-allocators ON FORCE)
set(resolve-countries OFF FORCE)
#set(shared OFF FORCE)
#set(tcmalloc OFF FORCE)
#set(unicode ON FORCE)
ENDIF(${TORRENT_DOWNLOADER} MATCHES ON)