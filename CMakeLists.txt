PROJECT( DDPS )

#CMAKE_MINIMUM_REQUIRED(VERSION 2.4)
CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

SET(BUILD_SHARED_LIBS ON)

OPTION(COMMUNITY_PORTAL "Add Community Support" ON)
OPTION(USER_UPLOAD "Add User Upload capabilities" ON)
OPTION(BUILTIN_BROWSER "Add the Built-in Browser Support" ON)
OPTION(CHAT_ENABLED "Add the Built-in Chat Support" OFF)
OPTION(DEVEL_TESTING "Skip the login routines" ON)
OPTION(DEBUG_MENU "Enable Debug Menu for Transfer Manager" ON)
OPTION(USE_WEBKIT "Enable use of wxWebKit for Browser" OFF)

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
SET(UPDATEURL updateddps.seancrazy.net CACHE STRING "Set the URL for AutoUpdate")
SET(CHAT_SERVER ddpschat.seancrazy.net CACHE STRING "Set the host for the Chat Server")

SET(DDPS_VERSION "1.0.0")
SET(DDPS_UPDATE_VERSION "1.0.0")
SET(CMAKE_FIND_LIBRARY_PREFIXES "")
SET(CMAKE_FIND_LIBRARY_SUFFIXES ".lib")
SET(wxWidgets_USE_LIBS base core net xml xrc)

SUBDIRS(libtorrent)
SUBDIRS(wxCURL)
SUBDIRS(webupdate)

INCLUDE( ${CMAKE_ROOT}/Modules/UsePkgConfig.cmake )

CONFIGURE_FILE(${CMAKE_SOURCE_DIR}/config.h.cmake
	${CMAKE_BINARY_DIR}/config.h ESCAPE_QUOTES)

SET(SRCS 
	AppCommon.cpp
	AppConfig.cpp
	AppFrame.cpp
	AppLogin.cpp
	AppMain.cpp
	AppMenu.cpp
	AppPanel.cpp
	AppUpdate.cpp
	BrowserEmbed.cpp
	HttpManager.cpp
	SettingsDialog.cpp
	TorrentAlertTimer.cpp
	TorrentBencode.cpp
	TorrentManager.cpp
	TorrentProperties.cpp
	TransferCommon.cpp
	TransferManager.cpp
	TransferManagerList.cpp
	TransferTimer.cpp
)

SET(UPDATE_SRCS
	webupdate/app/webapp.cpp
	webupdate/app/webupdatedlg.cpp
	webupdate/app/app.rc
	webupdate/app/app.xpm
	webupdate/app/www.xpm
	)

PKGCONFIG(libcurl CURL_INCLUDE_DIR CURL_LINK_DIR CURL_LINK_FLAGS CURL_CFLAGS)
FIND_PACKAGE(wxWidgets)
FIND_PACKAGE(Boost)

INCLUDE_DIRECTORIES(
	${CMAKE_SOURCE_DIR}
	${CMAKE_BINARY_DIR}
	${CURL_INCLUDE_DIR}
	contrib
	libtorrent/include
	libtorrent/include/libtorrent
	webupdate/include
	webupdate/app/
	wxCURL/include
)

LINK_DIRECTORIES(SHARED
	${CURL_LINK_DIR}
	/opt/local/lib
	/usr/lib
)

IF(WIN32)
	SET(GUI_TYPE WIN32)
	SET(SRCS ${SRCS} ${CMAKE_SOURCE_DIR}/contrib/ddps.rc)
ELSE(UNIX)
	IF(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
		SET(GUI_TYPE MACOSX_BUNDLE)
		SET(USE_WEBKIT ON)
	ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
ENDIF(WIN32)

IF(${USE_WEBKIT} MATCHES ON)
	SET(WEBKIT_LIBS wxwebkit)
ENDIF(${USE_WEBKIT} MATCHES ON)

IF(wxWidgets_FOUND)
	INCLUDE(
		${INCLUDE}
		${wxWidgets_USE_FILE}
	)
	INCLUDE_DIRECTORIES(
		${INCLUDE_DIRECTORIES}
		${wxWidgets_INCLUDE_DIRS}
	)
ENDIF(wxWidgets_FOUND)

IF(Boost_FOUND)
	INCLUDE_DIRECTORIES(
		${INCLUDE_DIRECTORIES}
		${Boost_INCLUDE_DIRS})
	LINK_DIRECTORIES(SHARED ${LINK_DIRECTORIES} ${Boost_LIBRARY_DIRS})
ENDIF(Boost_FOUND)


IF(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
	#MESSAGE("Using wxWebKitCtrl instead of wxMoz")
ELSE(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
	SET(USE_WXMOZ shipped CACHE SRING "Select system or shipped wxMozilla library")
	IF(${USE_WXMOZ} MATCHES "shipped")
		SUBDIRS(wxMoz)
		INCLUDE_DIRECTORIES(wxMoz)
		SET(wxMoz_LIB wxMoz)
	ELSE(${USE_WXMOZ} MATCHES "shipped")
		PKGCONFIG(wxmozilla WXMOZ_INCLUDE_DIR WXMOZ_LINK_DIR WXMOZ_LINK_FLAGS WXMOZ_CFLAGS)
		INCLUDE_DIRECTORIES(
			${INCLUDE_DIRECTORIES}
			${WXMOZ_INCLUDE_DIR}
		)
		LINK_DIRECTORIES(SHARED
			${LINK_DIRECTORIES}
			${WXMOZ_LINK_DIR}
		)
		SET(wxMoz_LIB "")
	ENDIF(${USE_WXMOZ} MATCHES "shipped")
ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")

IF(${CHAT_ENABLED} MATCHES ON)
	SUBDIRS(gloox/src)

	SET(SRCS ${SRCS}
		### Chat
		ChatCommon.cpp
		ChatConnection.cpp
		ChatConnectionThread.cpp
		ChatMessage.cpp
		ChatRoster.cpp
		ChatWindow.cpp
		ChatRosterData.cpp
	)

	INCLUDE_DIRECTORIES(
		${INCLUDE_DIRECTORIES}
		gloox/src
	)

	SET(gloox_LIB gloox)
ENDIF(${CHAT_ENABLED} MATCHES ON)

SET(CMAKE_EXE_LINKER_FLAGS ${CMAKE_EXE_LINKER_FLAGS} ${WXMOZ_LINK_FLAGS} ${CURL_LINK_FLAGS})


IF(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
	SET(MACOSX_EXTRAS_UPDATE webupdate/libwebupdate.dylib)
	SET(MACOSX_BUNDLE_INFO_STRING "")
	#SET(MACOSX_BUNDLE_ICON_FILE "${CMAKE_SOURCE_DIR}/contrib/ddps-update.icns")
	SET(MACOSX_BUNDLE_GUI_IDENTIFIER "")
	SET(MACOSX_BUNDLE_LONG_VERSION_STRING "")
	SET(MACOSX_BUNDLE_BUNDLE_NAME "${PROJECT_NAME}-Updater")
	SET(MACOSX_BUNDLE_SHORT_VERSION_STRING "")
	SET(MACOSX_BUNDLE_BUNDLE_VERSION "${DDPS_UPDATE_VERSION}")
	SET(MACOSX_BUNDLE_COPYRIGHT "Copyright 2008 Sean Nelson")
#	#SET_SOURCE_FILES_PROPERTIES(${MACOSX_EXTRAS_UPDATE} PROPERTIES MACOSX_PACKAGE_LOCATION MacOS)
ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
ADD_EXECUTABLE(DDPS-Updater ${GUI_TYPE} ${UPDATE_SRCS}) 
TARGET_LINK_LIBRARIES(DDPS-Updater webupdate ${wxWidgets_LIBRARIES})


IF(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
	SET(MACOSX_EXTRAS_UPDATE webupdate/libwebupdate.dylib)
	SET(MACOSX_EXTRAS 
		libtorrent/libtorrent.dylib
		wxCURL/libwxcurl.dylib
		${MACOSX_EXTRAS_UPDATE}
	)
	SET(MACOSX_BUNDLE_INFO_STRING "")
	SET(MACOSX_BUNDLE_ICON_FILE "${CMAKE_SOURCE_DIR}/contrib/ddps2.icns")
	SET(MACOSX_BUNDLE_GUI_IDENTIFIER "")
	SET(MACOSX_BUNDLE_LONG_VERSION_STRING "")
	SET(MACOSX_BUNDLE_BUNDLE_NAME "${PROJECT_NAME}")
	SET(MACOSX_BUNDLE_SHORT_VERSION_STRING "")
	SET(MACOSX_BUNDLE_BUNDLE_VERSION "${DDPS_VERSION}")
	SET(MACOSX_BUNDLE_COPYRIGHT 
		"Copyright 2008 Sean Nelson, Corey Brown, Joshua Barron, Adam Troemne")
	#SET_SOURCE_FILES_PROPERTIES(${MACOSX_EXTRAS} PROPERTIES MACOSX_PACKAGE_LOCATION MacOS)
ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
ADD_EXECUTABLE(DDPS ${GUI_TYPE} ${SRCS})
TARGET_LINK_LIBRARIES(DDPS torrent curl wxcurl ${wxMoz_LIB} ${wxWidgets_LIBRARIES} ${gloox_LIB} ${WEBKIT_LIBS})
