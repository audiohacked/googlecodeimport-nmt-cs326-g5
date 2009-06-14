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