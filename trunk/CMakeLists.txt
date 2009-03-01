PROJECT( DDPS )

CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

SET(BUILD_SHARED_LIBS ON)

OPTION(BUILTIN_BROWSER "Add the Built-in Browser Support" OFF)
OPTION(CHAT_ENABLED "Add the Built-in Chat Support" OFF)
OPTION(TORRENT "Add BitTorrent Support" OFF)
OPTION(UPDATER "Add Updater Support" OFF)
OPTION(DOWNLOADER "Add Downloader Support" OFF)
OPTION(BROKEN_ABOUTBOX "Enable the Broken AboutBox" OFF)
OPTION(COMMUNITY_PORTAL "Add Community Support" OFF)
OPTION(USER_UPLOAD "Add User Upload capabilities" ON)
OPTION(DEVEL_TESTING "Skip the login routines" ON)
OPTION(DEBUG_MENU "Enable Debug Menu for Transfer Manager" ON)
OPTION(USE_WEBKIT "Enable use of wxWebKit for Browser" OFF)
OPTION(IMG_BUTTONS "Enable use of Bitmap-styled Buttons" ON)

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
SET(wxWidgets_USE_LIBS base core net xml xrc)
CONFIGURE_FILE(${CMAKE_SOURCE_DIR}/config.h.cmake
	${CMAKE_BINARY_DIR}/config.h ESCAPE_QUOTES)

FIND_PACKAGE(wxWidgets)

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

IF(WIN32)
	SET(GUI_TYPE WIN32)
	#SET(SRCS ${SRCS} ${CMAKE_SOURCE_DIR}/contrib/ddps.rc)
ELSE(UNIX)
	IF(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
		SET(GUI_TYPE MACOSX_BUNDLE)
		SET(USE_WEBKIT ON)
	ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
ENDIF(WIN32)

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

SET(DDPS_LIBS "")

IF(${BUILTIN_BROWSER} MATCHES ON)
    SET(SRCS
        ${SRCS} 
    	BrowserEmbed.cpp
    )
    SUBDIRS(mozembed)
    INCLUDE_DIRECTORIES(mozembed/wx)
    SET(wxMoz_LIB mozembed)
    
    IF(${USE_WEBKIT} MATCHES ON)
        SET(WEBKIT_LIBS wxwebkit)
    ENDIF(${USE_WEBKIT} MATCHES ON)
    SET(DDPS_LIBS ${DDPS_LIBS} ${wxMoz_LIB} ${WEBKIT_LIBS})

    #IF(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
        #MESSAGE("Using wxWebKitCtrl instead of wxMoz")
    #ELSE(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    #	SET(USE_WXMOZ shipped CACHE SRING "Select system or shipped wxMozilla library")
    #	IF(${USE_WXMOZ} MATCHES "shipped")
    #		SUBDIRS(mozembed)
    #		INCLUDE_DIRECTORIES(mozembed)
    #		SET(wxMoz_LIB mozembed)
    #	ELSE(${USE_WXMOZ} MATCHES "shipped")
    #		PKG_CHECK_MODULES(WXMOZ wxmozilla)
    #		INCLUDE_DIRECTORIES(
    #			${INCLUDE_DIRECTORIES}
    #			${WXMOZ_INCLUDE_DIRS}
    #		)
    #		LINK_DIRECTORIES(SHARED
    #			${LINK_DIRECTORIES}
    #			${WXMOZ_LIBRARY_DIRS}
    #		)
    #		SET(wxMoz_LIB "")
    #	ENDIF(${USE_WXMOZ} MATCHES "shipped")
    #ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    SET(CMAKE_EXE_LINKER_FLAGS ${CMAKE_EXE_LINKER_FLAGS} ${WXMOZ_LDFLAGS})
ENDIF(${BUILTIN_BROWSER} MATCHES ON)


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

    SET(DDPS_LIBS ${DDPS_LIBS} ${gloox_LIB})
ENDIF(${CHAT_ENABLED} MATCHES ON)

IF(${DOWNLOADER} MATCHES ON)
    SET(SRCS
        ${SRCS} 
    	HttpManager.cpp
    	TransferCommon.cpp
    	TransferManager.cpp
    	TransferManagerList.cpp
    	TransferTimer.cpp
    )
    INCLUDE( ${CMAKE_ROOT}/Modules/FindPkgConfig.cmake )
    PKG_CHECK_MODULES(CURL REQUIRED libcurl)
    SUBDIRS(wxCURL)
    INCLUDE_DIRECTORIES(
        ${INCLUDE_DIRECTORIES}
        ${CURL_INCLUDE_DIRS}
        wxCURL/include
    )
    LINK_DIRECTORIES(SHARED
        ${LINK_DIRECTORIES}
    	${CURL_LIBRARY_DIRS}
    )
    SET(DDPS_LIBS ${DDPS_LIBS} curl wxcurl)
    IF(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
        SET(MACOSX_EXTRAS
            ${MACOSX_EXTRAS} 
            wxCURL/libwxcurl.dylib
        )
    ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")

    IF(${TORRENT} MATCHES ON)
        SET(DOWNLOADER ON)
        SET(SRCS
            ${SRCS} 
        	TorrentAlertTimer.cpp
        	TorrentBencode.cpp
        	TorrentManager.cpp
        	TorrentProperties.cpp
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
    SET(CMAKE_EXE_LINKER_FLAGS ${CMAKE_EXE_LINKER_FLAGS} ${CURL_LDFLAGS})
ENDIF(${DOWNLOADER} MATCHES ON)

IF(${UPDATER} MATCHES ON)
    SET(UPDATE_SRCS
    	webupdate/app/webapp.cpp
    	webupdate/app/webupdatedlg.cpp
    	webupdate/app/app.rc
    	webupdate/app/app.xpm
    	webupdate/app/www.xpm
    )
    SUBDIRS(webupdate)
    INCLUDE_DIRECTORIES(
        ${INCLUDE_DIRECTORIES}
        webupdate/include
        webupdate/app/
    )
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
        #SET_SOURCE_FILES_PROPERTIES(${MACOSX_EXTRAS_UPDATE} PROPERTIES MACOSX_PACKAGE_LOCATION MacOS)
    ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    ADD_EXECUTABLE(DDPS-Updater ${GUI_TYPE} ${UPDATE_SRCS}) 
    TARGET_LINK_LIBRARIES(DDPS-Updater webupdate ${wxWidgets_LIBRARIES})
ENDIF(${UPDATER} MATCHES ON)

INCLUDE_DIRECTORIES(
	${INCLUDE_DIRECTORIES}
	${CMAKE_SOURCE_DIR}
	${CMAKE_BINARY_DIR}
	contrib
)

LINK_DIRECTORIES(SHARED
    ${LINK_DIRECTORIES}
	/opt/local/lib
	/usr/lib
)

IF(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
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
TARGET_LINK_LIBRARIES(DDPS ${wxWidgets_LIBRARIES} ${DDPS_LIBS})
