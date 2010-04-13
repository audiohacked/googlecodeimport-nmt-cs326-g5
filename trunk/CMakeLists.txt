PROJECT( DDPS )

CMAKE_MINIMUM_REQUIRED( VERSION 2.6 FATAL_ERROR )

if (NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE Release FORCE)
endif (NOT CMAKE_BUILD_TYPE)

OPTION( BUILD_SHARED_LIBS "Set to OFF to build static libraries"  ON )
#SET(CMAKE_CONFIGURATION_TYPES Debug Release RelWithDebInfo)

OPTION(BUILTIN_BROWSER    "Add the Built-in Browser Support"          ON)
OPTION(CHAT_ENABLED       "Add the Built-in Chat Support"             ON)
OPTION(COMMUNITY_PORTAL   "Add the Built-in Community Support"        ON)
OPTION(CRYPTO             "Add Crypto via QCA"                       OFF)
OPTION(DOWNLOADER         "Add the Built-in Downloader Support"       ON)
#OPTION(DEVEL_TESTING      "Skip the login routines"                   ON)
#OPTION(DEBUG_MENU         "Enable Debug Menu for Transfer Manager"   OFF)
#OPTION(IMG_BUTTONS        "Enable use of Bitmap-styled Buttons"      OFF)
OPTION(HTTP_DOWNLOADER    "Add the Built-in HTTP Downloader Support"  ON)
OPTION(TORRENT_DOWNLOADER "Add the Built-in BitTorrent Support"      OFF)
OPTION(UPDATER            "Add the Built-in Updater Support"         OFF)

SET(HOMEPAGE
	http://ddps.seancrazy.net/
	CACHE STRING "Set the URL for Homepage")
SET(NEWSPAGE
	http://ddps.seancrazy.net/news
	CACHE STRING "Set the URL for Newspage")
SET(SUPPORTPAGE
	http://ddps.seancrazy.net/support
	CACHE STRING "Set the URL for Supportpage")
SET(COMMUNITYPAGE
	http://ddps.seancrazy.net/community
	CACHE STRING "Set the URL for Community Portal")
SET(UPDATEURL
	updateddps.seancrazy.net
	CACHE STRING "Set the URL for AutoUpdate")
SET(CHAT_SERVER
	ddps-chat.seancrazy.net
	CACHE STRING "Set the host for the Chat Server")

SET(DDPS_VERSION "1.0.0")
SET(DDPS_UPDATE_VERSION "1.0.0")
SET(CMAKE_FIND_LIBRARY_PREFIXES "")
SET(CMAKE_FIND_LIBRARY_SUFFIXES ".lib")

SET(SRCS 
#	AppCommon.cpp
	AppConfig.cpp
	AppWidget.cpp
	AppLogin.cpp
	AppMain.cpp
#	AppMenu.cpp
#	AppUpdate.cpp
	SettingsDialog.cpp
)

SET(HDRS 
#	AppCommon.h
	AppConfig.h
	AppWidget.h
	AppLogin.h
	AppMain.h
#	AppMenu.h
#	AppUpdate.h
	SettingsDialog.h
	${CMAKE_BINARY_DIR}/config.h
)

SET(DDPS_LIBS "")

FIND_PACKAGE(Qt4 REQUIRED )
SET(QT_USE_QTWEBKIT TRUE)
SET(QT_USE_QTNETWORK TRUE)
#SET(QT_USE_QTXML TRUE)
#SET(QT_USE_QTSQL TRUE)
#SET(QT_USE_QTUITOOLS TRUE)
INCLUDE(${QT_USE_FILE})

INCLUDE_DIRECTORIES(
	${INCLUDE_DIRECTORIES}
	${CMAKE_SOURCE_DIR}
	${CMAKE_BINARY_DIR}
#	${CMAKE_SOURCE_DIR}/contrib
)

LINK_DIRECTORIES(
	${LINK_DIRECTORIES}
	${CMAKE_BINARY_DIR}
)

INCLUDE( ${CMAKE_SOURCE_DIR}/cmake/option_logic.cmake )
INCLUDE( ${CMAKE_SOURCE_DIR}/cmake/sys_linux.cmake )
INCLUDE( ${CMAKE_SOURCE_DIR}/cmake/sys_osx.cmake )
INCLUDE( ${CMAKE_SOURCE_DIR}/cmake/sys_win32.cmake )
INCLUDE( ${CMAKE_SOURCE_DIR}/cmake/boost.cmake )
INCLUDE( ${CMAKE_SOURCE_DIR}/cmake/qca.cmake )
INCLUDE( ${CMAKE_SOURCE_DIR}/cmake/libtorrent.cmake )
INCLUDE( ${CMAKE_SOURCE_DIR}/cmake/gloox.cmake )
INCLUDE( ${CMAKE_SOURCE_DIR}/cmake/browser.cmake )
INCLUDE( ${CMAKE_SOURCE_DIR}/cmake/chat.cmake )
INCLUDE( ${CMAKE_SOURCE_DIR}/cmake/downloader.cmake )
INCLUDE( ${CMAKE_SOURCE_DIR}/cmake/downloader_http.cmake )
INCLUDE( ${CMAKE_SOURCE_DIR}/cmake/downloader_torrent.cmake )
#INCLUDE( ${CMAKE_SOURCE_DIR}/cmake/updater.cmake )
#INCLUDE( ${CMAKE_SOURCE_DIR}/cmake/custom_commands.cmake )
#INCLUDE( ${CMAKE_SOURCE_DIR}/cmake/packaging.cmake )

CONFIGURE_FILE(${CMAKE_SOURCE_DIR}/config.h.cmake
	${CMAKE_BINARY_DIR}/config.h ESCAPE_QUOTES)

QT4_WRAP_CPP( MOC_SRCS ${HDRS})

ADD_EXECUTABLE(DDPS ${SRCS} ${HDRS} ${MOC_SRCS})
TARGET_LINK_LIBRARIES(DDPS ${QT_LIBRARIES} ${DDPS_LIBS})
