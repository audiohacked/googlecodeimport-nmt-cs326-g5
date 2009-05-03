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