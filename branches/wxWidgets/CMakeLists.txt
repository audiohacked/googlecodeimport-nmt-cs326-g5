PROJECT( DDPS )

CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

SET(BUILD_SHARED_LIBS OFF)
#SET(CMAKE_CONFIGURATION_TYPES Debug Release RelWithDebInfo)

OPTION(BROKEN_ABOUTBOX    "Enable the Broken AboutBox"                ON)
OPTION(BUILTIN_BROWSER    "Add the Built-in Browser Support"         OFF)
OPTION(CHAT_ENABLED       "Add the Built-in Chat Support"            OFF)
OPTION(COMMUNITY_PORTAL   "Add the Built-in Community Support"       OFF)
OPTION(DOWNLOADER         "Add the Built-in Downloader Support"      OFF)
OPTION(DEVEL_TESTING      "Skip the login routines"                   ON)
OPTION(DEBUG_MENU         "Enable Debug Menu for Transfer Manager"   OFF)
OPTION(IMG_BUTTONS        "Enable use of Bitmap-styled Buttons"       ON)
OPTION(HTTP_DOWNLOADER    "Add the Built-in HTTP Downloader Support" OFF)
OPTION(TORRENT_DOWNLOADER "Add the Built-in BitTorrent Support"      OFF)
OPTION(TORRENT            "Add the Built-in BitTorrent Support"      OFF)
OPTION(UPDATER            "Add the Built-in Updater Support"         OFF)
OPTION(USER_UPLOAD        "Add User Upload capabilities"             OFF)
OPTION(USE_WEBKIT         "Enable use of wxWebKit for Browser"       OFF)

SET(NEWSPAGE
	http://ddps.seancrazy.net/news
	CACHE STRING "Set the URL for Newspage")
SET(HOMEPAGE
	http://ddps.seancrazy.net/
	CACHE STRING "Set the URL for Homepage")
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
	ddpschat.seancrazy.net
	CACHE STRING "Set the host for the Chat Server")

SET(DDPS_VERSION "1.0.0")
SET(DDPS_UPDATE_VERSION "1.0.0")
SET(CMAKE_FIND_LIBRARY_PREFIXES "")
SET(CMAKE_FIND_LIBRARY_SUFFIXES ".lib")
SET(wxWidgets_USE_DEBUG ON)
SET(wxWidgets_USE_STATIC ON)

FIND_PACKAGE(wxWidgets COMPONENTS base core net xml xrc)

SET(SRCS 
	AppCommon.cpp
	AppConfig.cpp
	AppFrame.cpp
	AppLogin.cpp
	AppMain.cpp
	AppMenu.cpp
	AppPanel.cpp
	AppUpdate.cpp
	SettingsDialog.cpp
)

SET(HDRS 
	AppCommon.h
	AppConfig.h
	AppFrame.h
	AppLogin.h
	AppMain.h
	AppMenu.h
	AppPanel.h
	AppUpdate.h
	SettingsDialog.h
	${CMAKE_BINARY_DIR}/config.h
)

SET(DDPS_LIBS "")

INCLUDE_DIRECTORIES(
	${INCLUDE_DIRECTORIES}
	${CMAKE_SOURCE_DIR}
	${CMAKE_BINARY_DIR}
	${CMAKE_SOURCE_DIR}/contrib
)

LINK_DIRECTORIES(
    ${LINK_DIRECTORIES}
	${CMAKE_BINARY_DIR}
)

IF(wxWidgets_FOUND)
	INCLUDE(
		${wxWidgets_USE_FILE}
	)
	INCLUDE_DIRECTORIES(
		${INCLUDE_DIRECTORIES}
		${wxWidgets_INCLUDE_DIRS}
	)
ENDIF(wxWidgets_FOUND)

INCLUDE( ${CMAKE_SOURCE_DIR}/contrib/ddps_option_logic.cmake )

INCLUDE( ${CMAKE_SOURCE_DIR}/contrib/ddps_sys_linux.cmake )
INCLUDE( ${CMAKE_SOURCE_DIR}/contrib/ddps_sys_osx.cmake )
INCLUDE( ${CMAKE_SOURCE_DIR}/contrib/ddps_sys_win32.cmake )

INCLUDE( ${CMAKE_SOURCE_DIR}/contrib/ddps_browser.cmake )
INCLUDE( ${CMAKE_SOURCE_DIR}/contrib/ddps_chat.cmake )
INCLUDE( ${CMAKE_SOURCE_DIR}/contrib/ddps_downloader.cmake )
INCLUDE( ${CMAKE_SOURCE_DIR}/contrib/ddps_downloader_http.cmake )
INCLUDE( ${CMAKE_SOURCE_DIR}/contrib/ddps_downloader_torrent.cmake )
INCLUDE( ${CMAKE_SOURCE_DIR}/contrib/ddps_updater.cmake )

CONFIGURE_FILE(${CMAKE_SOURCE_DIR}/config.h.cmake
	${CMAKE_BINARY_DIR}/config.h ESCAPE_QUOTES)

INCLUDE( ${CMAKE_SOURCE_DIR}/contrib/ddps_custom_commands.cmake )

ADD_EXECUTABLE(DDPS ${GUI_TYPE} ${SRCS} ${HDRS})
TARGET_LINK_LIBRARIES(DDPS ${wxWidgets_LIBRARIES} ${DDPS_LIBS})
