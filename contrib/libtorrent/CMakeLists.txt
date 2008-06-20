PROJECT(libtorrent)

#SET(TOOLSET)
#SET(TARGET_OS)
#SET(VARIANT)
FIND_PACKAGE(Boost)
IF(${Boost_FOUND})
	INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS})
	LINK_DIRECTORIES(${Boost_LIBRARY_DIRS})
ENDIF(${Boost_FOUND})

SET(SRCS
	src/alert.cpp
	src/assert.cpp
	src/connection_queue.cpp
	src/entry.cpp
	src/escape_string.cpp
	src/http_connection.cpp
	src/http_stream.cpp
	src/identify_client.cpp
	src/ip_filter.cpp
	src/peer_connection.cpp
	src/bt_peer_connection.cpp
	src/web_peer_connection.cpp
	src/instantiate_connection.cpp
	src/natpmp.cpp
	src/piece_picker.cpp
	src/policy.cpp
	src/session.cpp
	src/session_impl.cpp
	src/socks4_stream.cpp
	src/socks5_stream.cpp
	src/stat.cpp
	src/storage.cpp
	src/torrent.cpp
	src/torrent_handle.cpp
	src/torrent_info.cpp
	src/tracker_manager.cpp
	src/http_tracker_connection.cpp
	src/udp_tracker_connection.cpp
	src/sha1.cpp
	src/metadata_transfer.cpp
	src/upnp.cpp
	src/ut_pex.cpp
	src/logger.cpp
	src/file_pool.cpp
	src/lsd.cpp
	src/disk_io_thread.cpp
	src/enum_net.cpp
	src/broadcast_socket.cpp
)

SET(KADEMLIA_SRCS
	src/kademlia/closest_nodes.cpp
	src/kademlia/dht_tracker.cpp
	src/kademlia/node.cpp
	src/kademlia/refresh.cpp
	src/kademlia/rpc_manager.cpp
	src/kademlia/find_data.cpp
	src/kademlia/node_id.cpp
	src/kademlia/routing_table.cpp
	src/kademlia/traversal_algorithm.cpp
)

SET(ZLIB_SRCS
	zlib/adler32.c
	zlib/compress.c
	zlib/crc32.c
	zlib/deflate.c
	zlib/gzio.c
	zlib/infback.c
	zlib/inffast.c
	zlib/inflate.c
	zlib/inftrees.c
	zlib/trees.c
	zlib/uncompr.c
	zlib/zutil.c
)

SET(LIBLINK "")


#NEED_LIBRT: YES NO
OPTION(NEED_LIBRT "" OFF)
IF(${NEED_LIBRT} MATCHES ON)
	SET(LIBLINK rt)
ENDIF(${NEED_LIBRT} MATCHES ON)


#INVARIANT_CHECKS: ON OFF
OPTION(INVARIANT_CHECKS "" ON)
IF(${INVARIANT_CHECKS} MATCHES OFF)
	SET_SOURCE_FILES_PROPERTIES(${SRCS} COMPILE_FLAGS -DTORRENT_DISABLE_INVARIANT_CHECKS)
ENDIF(${INVARIANT_CHECKS} MATCHES OFF)


#DISK_STATS: OFF ON
OPTION(DISK_STATS "" OFF)
IF(${DISK_STATS} MATCHES ON)
	SET_SOURCE_FILES_PROPERTIES(${SRCS} COMPILE_FLAGS -DTORRENT_DISK_STATS)
ENDIF(${DISK_STATS} MATCHES ON)


#LOGGING: NONE DEFAULT VERBOSE
SET(LOGGING "None" CACHE STRING "Logging: None, Default, Verbose")
IF(${LOGGING} MATCHES "None")
ELSE()
	IF(${LOGGING} MATCHES "Default")
		SET_SOURCE_FILES_PROPERTIES(${SRCS} COMPILE_FLAGS -DTORRENT_LOGGING)
	ELSE()
		IF(${LOGGING} MATCHES "Verbose")
			SET_SOURCE_FILES_PROPERTIES(${SRCS} COMPILE_FLAGS -DTORRENT_VERBOSE_LOGGING)
		ENDIF(${LOGGING} MATCHES "Verbose")
	ENDIF(${LOGGING} MATCHES "Default")
ENDIF(${LOGGING} MATCHES "None")

#DHT_SUPPORT: ON OFF LOGGING
SET(DHT ON CACHE STRING "DHT Support: On, Off, Logging")
IF(${DHT} MATCHES "Off")
	SET_SOURCE_FILES_PROPERTIES(${SRCS} COMPILE_FLAGS -DTORRENT_DISABLE_DHT)
ELSE()
	IF(${DHT} MATCHES "Logging")
		SET_SOURCE_FILES_PROPERTIES(${SRCS} COMPILE_FLAGS -DTORRENT_DHT_VERBOSE_LOGGING)
	ELSE()
	ENDIF(${DHT} MATCHES "Logging")
	SET(SRCS ${SRCS} ${KADEMLIA_SRCS})
ENDIF(${DHT} MATCHES "Off")


#OPENSSL: PE SHA_1 OFF
SET(OPENSSL PE CACHE STRING "Openssl support: PE, SHA_1, OFF")
IF(${OPENSSL} MATCHES OFF)
	SET(SRCS ${SRCS} src/sha1.cpp)
	SET_SOURCE_FILES_PROPERTIES(${SRCS} 
		COMPILE_FLAGS -DTORRENT_DISABLE_ENCRYPTION
	)
ELSE(${OPENSSL} MATCHES OFF)
	IF(WIN32)
		SET(LIBLINK ${LIBLINK} gdi32)
		IF(NOT GCC)
			SET(LIBLINK ${LIBLINK} ssleay32 libeay32 advapi32 user32 shell32)
		ELSE()
			SET(LIBLINK ${LIBLINK} ws2_32 wsock32)
			SET_SOURCE_FILES_PROPERTIES(${SRCS} 
				COMPILE_FLAGS -DWIN32_LEAN_AND_MEAN -D_WIN32_WINNT=0x0500 
				-D__USE_W32_SOCKETS -DWIN32 -D_WIN32)
		ENDIF(NOT GCC)
	ELSE(WIN32)
		SET(LIBLINK ${LIBLINK} crypto)
	ENDIF(WIN32)
	
	IF(${OPENSSL} MATCHES "PE")
		SET(SRCS ${SRCS} src/pe_crypto.cpp)
		SET_SOURCE_FILES_PROPERTIES(${SRCS} COMPILE_FLAGS -DTORRENT_USE_OPENSSL)
	ENDIF(${OPENSSL} MATCHES "PE")
	IF(${OPENSSL} MATCHES "SHA_1")
		SET_SOURCE_FILES_PROPERTIES(${SRCS} 
			COMPILE_FLAGS -DTORRENT_USE_OPENSSL -DTORRENT_DISABLE_ENCRYPTION)
	ENDIF(${OPENSSL} MATCHES "SHA_1")
ENDIF(${OPENSSL} MATCHES OFF)


#RESOLVE_COUNTRIES: ON OFF
OPTION(RESOLVE_COUNTRIES "" ON)
IF(${RESOLVE_COUNTRIES} MATCHES OFF)
	SET_SOURCE_FILES_PROPERTIES(${SRCS} 
		COMPILE_FLAGS -DTORRENT_DISABLE_RESOLVE_COUNTRIES)
ENDIF(${RESOLVE_COUNTRIES} MATCHES OFF)



#CHARACTER_SET: ANSI UNICODE
SET(CHARACTER_SET ANSI CACHE STRING "UNICODE or ANSI")
IF(${CHARACTER_SET} MATCHES "UNICODE")
	SET_SOURCE_FILES_PROPERTIES(${SRCS} 
		COMPILE_FLAGS -D_UNICODE -DUNICODE)	
ENDIF(${CHARACTER_SET} MATCHES "UNICODE")


#ZLIB: SHIPPED SYSTEM
SET(ZLIB SHIPPED CACHE STRING "Zlib support: SHIPPED or SYSTEM")
IF(${ZLIB} MATCHES SYSTEM)
	SET(LIBLINK ${LIBLINK} z)
ELSE()
	INCLUDE_DIRECTORIES(${INCLUDE_DIRECTORIES} ./zlib)
	SET(SRCS ${SRCS} ${ZLIB_SRCS})
ENDIF(${ZLIB} MATCHES SYSTEM)


#STATISTICS: OFF ON
OPTION(STATISTICS "" OFF)
IF(${STATISTICS} MATCHES ON)
	SET_SOURCE_FILES_PROPERTIES(${SRCS} 
		COMPILE_FLAGS -DTORRENT_STATS)	
ENDIF(${STATISTICS} MATCHES ON)


#UPNP_LOGGING: OFF ON
OPTION(UPNP_LOGGING "" OFF)
IF(${UPNP_LOGGING} MATCHES ON)
	SET_SOURCE_FILES_PROPERTIES(${SRCS} 
		COMPILE_FLAGS -DTORRENT_UPNP_LOGGING)	
ENDIF(${UPNP_LOGGING} MATCHES ON)


#BOOST: SYSTEM SOURCE
SET(BOOST SYSTEM CACHE STRING "Boost library: SYSTEM or SOURCE")
IF(${BOOST} MATCHES "SYSTEM")
	SET(LIBLINK ${LIBLINK} boost_filesystem-mt boost_thread-mt boost_system-mt)
ELSE()
	SET(LIBLINK ${LIBLINK} 
		/boost/thread//boost_thread
		/boost/filesystem//boost_filesystem
	)
	INCLUDE_DIRECTORIES(
		${INCLUDE_DIRECTORIES}
		${BOOST_ROOT}
	)
	SET_SOURCE_FILES_PROPERTIES(${SRCS} 
		COMPILE_FLAGS -DBOOST_ALL_NO_LIB)
		
ENDIF(${BOOST} MATCHES "SYSTEM")


#DEBUG_ITERATORS: OFF ON
OPTION(DEBUG_ITERATORS "" OFF)
IF(${DEBUG_ITERATORS} MATCHES ON)
	SET_SOURCE_FILES_PROPERTIES(${SRCS} 
		COMPILE_FLAGS -D_SCL_SECURE=1 -D_GLIBCXX_DEBUG)	
ENDIF(${DEBUG_ITERATORS} MATCHES ON)


#TEST_COVERAGE: OFF ON
OPTION(TEST_COVERAGE "" OFF)
IF(${TEST_COVERAGE} MATCHES ON)
	IF(NOT WIN32) # gcc && darwin
		SET_SOURCE_FILES_PROPERTIES(${SRCS} 
			COMPILE_FLAGS -fprofile-arcs -ftest-coverage)
	ENDIF(NOT WIN32)
ENDIF(${TEST_COVERAGE} MATCHES ON)


#IF(${VARIANT} MATCHES "Debug")
#	IF(UNIX)
#		IF(${CMAKE_BUILD_SYSTEM} MATCHES "Linux")
#			SET_SOURCE_FILES_PROPERTIES(${SRCS} 
#				COMPILE_FLAGS -export-dynamic -rdynamic)
#		ENDIF(${CMAKE_BUILD_SYSTEM} MATCHES "Linux")
#	ENDIF(UNIX)
#ELSE()
	SET_SOURCE_FILES_PROPERTIES(${SRCS} 
		COMPILE_FLAGS -DNDEBUG)	
#ENDIF(${VARIANT} MATCHES "Debug")

# IF(${TOOLSET} MATCHES "MSVC")
	# these compiler settings just makes the compiler standard conforming
	#	<toolset>msvc:<cxxflags>/Zc:wchar_t
	#	<toolset>msvc:<cxxflags>/Zc:forScope
	# disable bogus deprecation warnings on msvc8
	#	<toolset>msvc:<define>_SCL_SECURE_NO_DEPRECATE
	#	<toolset>msvc:<define>_CRT_SECURE_NO_DEPRECATE
	# msvc optimizations
	#	<toolset>msvc,<variant>release:<linkflags>/OPT:ICF=5
	#	<toolset>msvc,<variant>release:<linkflags>/OPT:REF
	# disable warning C4503: decorated name length exceeded, name was truncated
	#	<toolset>msvc:<cxxflags>/wd4503
	# disable some warnings for gcc
#ELSE()
	#	<toolset>gcc:<cxxflags>-fno-strict-aliasing
	#	<toolset>gcc:<cxxflags>-Wno-missing-braces
#ENDIF()

IF(WIN32)
	SET(SRCS
		${SRCS}
		src/file_win.cpp
	)
ENDIF(WIN32)

IF(UNIX)
	#SET(SRCS ${SRCS} src/assert.cpp)
	SET(SRCS ${SRCS} src/file.cpp)
	IF(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
	ELSE(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
	ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
ENDIF(UNIX)

SET_SOURCE_FILES_PROPERTIES(${SRCS} 
	COMPILE_FLAGS -D_FILE_OFFSET_BITS=64 
	COMPILE_FLAGS -DBOOST_MULTI_INDEX_DISABLE_SERIALIZATION
	COMPILE_FLAGS -DBOOST_THREAD_USE_LIB
)

INCLUDE_DIRECTORIES(
	${INCLUDE_DIRECTORIES}
	./include
	./include/libtorrent
)

LINK_DIRECTORIES(
	${LINK_DIRECTORIES}
	/opt/local/lib
	/usr/lib
	/usr/local/lib
	/sw/lib
)

#LINK_LIBRARIES()
ADD_LIBRARY(libtorrent SHARED ${SRCS})
TARGET_LINK_LIBRARIES(libtorrent ${LIBLINK})
