PROJECT( DDPS )

CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

SET(BUILD_SHARED_LIBS ON)

OPTION(BUILTIN_BROWSER "Add the Built-in Browser Support" OFF)
OPTION(CHAT_ENABLED "Add the Built-in Chat Support" ON)
OPTION(TORRENT "Add BitTorrent Support" OFF)
OPTION(UPDATER "Add Updater Support" OFF)
OPTION(DOWNLOADER "Add Downloader Support" OFF)
OPTION(BROKEN_ABOUTBOX "Enable the Broken AboutBox" OFF)
OPTION(COMMUNITY_PORTAL "Add Community Support" OFF)
OPTION(USER_UPLOAD "Add User Upload capabilities" OFF)
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
	contrib
)

LINK_DIRECTORIES(
    ${LINK_DIRECTORIES}
	${CMAKE_BINARY_DIR}
	/opt/local/lib
	/usr/lib
)

IF(WIN32)
	SET(GUI_TYPE WIN32)
	#SET(CMAKE_EXE_LINKER_FLAGS ${CMAKE_EXE_LINKER_FLAGS} -DWIN32)
	#ADD_DEFINITIONS(-DWIN32)

	#SET(SRCS ${SRCS} ${CMAKE_SOURCE_DIR}/contrib/ddps.rc)
	#SET(SYS_WIN32_LIBS comctl32.lib rpcrt4.lib winmm.lib advapi32.lib wsock32.lib)
	#SET(DDPS_LIBS ${DDPS_LIBS} ${SYS_WIN32_LIBS})
	IF(MSVC)
	#	# msvc2005 deprecated warnings
		add_definitions(-D_CRT_SECURE_NO_DEPRECATE -D_CRT_NONSTDC_NO_DEPRECATE -Zc:wchar_t-)
	#	# calm mdown msvc
	#	add_definitions(-wd4251) # 'identifier' : class 'type' needs to have dll-interface to be used by clients of class 'type2'
	#	add_definitions(-wd4275) # non  DLL-interface classkey 'identifier' used as base for DLL-interface classkey 'identifier'
	#	add_definitions(-wd4309) # 'conversion' : truncation of constant value
	#	add_definitions(-wd4503) # decorated name length exceeded
	#	add_definitions(-wd4786) # identifier was truncated to '255' characters in the debug information
	ENDIF(MSVC)
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

IF(${BUILTIN_BROWSER} MATCHES ON)
    SET(SRCS ${SRCS} 
    	BrowserEmbed.cpp
    )
    SET(HDRS ${HDRS} 
    	BrowserEmbed.h
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
#    include( FindZLIB )
#    include( CheckFunctionExists )
    
#    check_function_exists( setsockopt SETSOCKOPT_EXISTS )
    
#    if( SETSOCKOPT_EXISTS )
#            write_file( ${CMAKE_CURRENT_SOURCE_DIR}/config.h "#define HAVE_SETSOCKOPT 1")
#    endif( SETSOCKOPT_EXISTS )
#    
#    if( ZLIB_FOUND )
#        set( LIBS ${LIBS} ${ZLIB_LIBRARIES} )
#        set( INCLUDE_DIRS ${INCLUDE_DIRS} ${ZLIB_INCLUDE_DIR} )
#        write_file( ${CMAKE_CURRENT_SOURCE_DIR}/config.h "#define HAVE_ZLIB 1" APPEND )
#    else( ZLIB_FOUND )
        SET(LIBS ${LIBS} wsock32.lib crypt32.lib secur32.lib dnsapi.lib)
#    endif( ZLIB_FOUND)
    
	SUBDIRS(gloox/src)
	
	SET(SRCS ${SRCS}
		ChatCommon.cpp
		ChatConnection.cpp
		ChatConnectionThread.cpp
		ChatMessage.cpp
		ChatRoster.cpp
		ChatWindow.cpp
		ChatRosterData.cpp
	)
	SET(HDRS ${HDRS}
		ChatCommon.h
		ChatConnection.h
		ChatConnectionThread.h
		ChatMessage.h
		ChatRoster.h
		ChatWindow.h
		ChatRosterData.h
	)
	INCLUDE_DIRECTORIES(
		${INCLUDE_DIRECTORIES}
		gloox/src
	)
	SET(gloox_LIB gloox)
    SET(DDPS_LIBS ${DDPS_LIBS} ${gloox_LIB})
ENDIF(${CHAT_ENABLED} MATCHES ON)

IF(${DOWNLOADER} MATCHES ON)
    SET(CMAKE_EXE_LINKER_FLAGS ${CMAKE_EXE_LINKER_FLAGS} -DNDEBUG -DCURL_STATICLIB -DUSE_WINSOCK=1 -DWXUSINGDLL)
	ADD_DEFINITIONS( -DNDEBUG -DCURL_STATICLIB -DUSE_WINSOCK=1 -DWXUSINGDLL)
	IF(WIN32)
		SET(WIN32_CURL_LIB wsock32.lib winmm.lib)
	ENDIF(WIN32)

	SET(DDPS_LIBS ${DDPS_LIBS} libcurl wxcurl)

    SET(SRCS ${SRCS} 
    	HttpManager.cpp
    	TransferCommon.cpp
    	TransferManager.cpp
    	TransferManagerList.cpp
    	TransferTimer.cpp
    )
    SET(HDRS ${HDRS} 
    	HttpManager.h
    	TransferCommon.h
    	TransferManager.h
    	TransferManagerList.h
    	TransferTimer.h
    )
	SET(CURL_SRCS
		wxCURL/thirdparty/curl/lib/base64.c
		wxCURL/thirdparty/curl/lib/connect.c
		wxCURL/thirdparty/curl/lib/content_encoding.c
		wxCURL/thirdparty/curl/lib/cookie.c
		wxCURL/thirdparty/curl/lib/dict.c
		wxCURL/thirdparty/curl/lib/easy.c
		wxCURL/thirdparty/curl/lib/escape.c
		wxCURL/thirdparty/curl/lib/file.c
		wxCURL/thirdparty/curl/lib/formdata.c
		wxCURL/thirdparty/curl/lib/ftp.c
		wxCURL/thirdparty/curl/lib/getenv.c
		wxCURL/thirdparty/curl/lib/getinfo.c
		wxCURL/thirdparty/curl/lib/gtls.c
		wxCURL/thirdparty/curl/lib/hash.c
		wxCURL/thirdparty/curl/lib/hostares.c
		wxCURL/thirdparty/curl/lib/hostasyn.c
		wxCURL/thirdparty/curl/lib/hostip.c
		wxCURL/thirdparty/curl/lib/hostip4.c
		wxCURL/thirdparty/curl/lib/hostip6.c
		wxCURL/thirdparty/curl/lib/hostsyn.c
		wxCURL/thirdparty/curl/lib/hostthre.c
		wxCURL/thirdparty/curl/lib/http.c
		wxCURL/thirdparty/curl/lib/http_chunks.c
		wxCURL/thirdparty/curl/lib/http_digest.c
		wxCURL/thirdparty/curl/lib/http_negotiate.c
		wxCURL/thirdparty/curl/lib/http_ntlm.c
		wxCURL/thirdparty/curl/lib/if2ip.c
		wxCURL/thirdparty/curl/lib/inet_ntop.c
		wxCURL/thirdparty/curl/lib/inet_pton.c
		wxCURL/thirdparty/curl/lib/krb4.c
		wxCURL/thirdparty/curl/lib/ldap.c
		wxCURL/thirdparty/curl/lib/llist.c
		wxCURL/thirdparty/curl/lib/md5.c
		wxCURL/thirdparty/curl/lib/memdebug.c
		wxCURL/thirdparty/curl/lib/mprintf.c
		wxCURL/thirdparty/curl/lib/multi.c
		wxCURL/thirdparty/curl/lib/netrc.c
		wxCURL/thirdparty/curl/lib/parsedate.c
		wxCURL/thirdparty/curl/lib/progress.c
		wxCURL/thirdparty/curl/lib/security.c
		wxCURL/thirdparty/curl/lib/select.c
		wxCURL/thirdparty/curl/lib/sendf.c
		wxCURL/thirdparty/curl/lib/share.c
		wxCURL/thirdparty/curl/lib/socks.c
		wxCURL/thirdparty/curl/lib/speedcheck.c
		wxCURL/thirdparty/curl/lib/splay.c
		wxCURL/thirdparty/curl/lib/ssh.c
		wxCURL/thirdparty/curl/lib/sslgen.c
		wxCURL/thirdparty/curl/lib/ssluse.c
		wxCURL/thirdparty/curl/lib/strdup.c
		wxCURL/thirdparty/curl/lib/strequal.c
		wxCURL/thirdparty/curl/lib/strerror.c
		wxCURL/thirdparty/curl/lib/strtok.c
		wxCURL/thirdparty/curl/lib/strtoofft.c
		wxCURL/thirdparty/curl/lib/telnet.c
		wxCURL/thirdparty/curl/lib/tftp.c
		wxCURL/thirdparty/curl/lib/timeval.c
		wxCURL/thirdparty/curl/lib/transfer.c
		wxCURL/thirdparty/curl/lib/url.c
		wxCURL/thirdparty/curl/lib/version.c
	)
	SET(WXCURL_SRCS
		wxCURL/src/base.cpp
		wxCURL/src/dav.cpp
		wxCURL/src/davtool.cpp
		wxCURL/src/dialog.cpp
		wxCURL/src/ftp.cpp
		wxCURL/src/ftpparse.cpp
		wxCURL/src/ftptool.cpp
		wxCURL/src/http.cpp
		wxCURL/src/panel.cpp
		wxCURL/src/telnet.cpp
		wxCURL/src/thread.cpp
		wxCURL/src/utils.cpp
	)
	
    INCLUDE_DIRECTORIES(
        ${INCLUDE_DIRECTORIES}
        wxCURL/thirdparty/curl/include
		wxCURL/thirdparty/curl/lib
        wxCURL/include
    )
	
	ADD_LIBRARY(libcurl STATIC ${CURL_SRCS})
    TARGET_LINK_LIBRARIES(libcurl ${WIN32_CURL_LIB})
	ADD_LIBRARY(wxcurl STATIC ${WXCURL_SRCS})
    TARGET_LINK_LIBRARIES(wxcurl ${wxWidgets_LIBRARIES} ${WIN32_CURL_LIB} libcurl)

    IF(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
        SET(MACOSX_EXTRAS
            ${MACOSX_EXTRAS} 
            wxCURL/libwxcurl.dylib
        )
    ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")

    IF(${TORRENT} MATCHES ON)
        SET(DOWNLOADER ON)
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
    SET(CMAKE_EXE_LINKER_FLAGS ${CMAKE_EXE_LINKER_FLAGS} ${CURL_LDFLAGS})
ENDIF(${DOWNLOADER} MATCHES ON)

IF(${UPDATER} MATCHES ON)
    #SET(CMAKE_EXE_LINKER_FLAGS ${CMAKE_EXE_LINKER_FLAGS} ${CURL_LDFLAGS} -DWXUSINGDLL)
	#ADD_DEFINITIONS(-DWXUSINGDLL)
    SET(WEBUPDATE_SRCS
        webupdate/src/checkedlistctrl.cpp
        webupdate/src/download.cpp
        webupdate/src/installer.cpp
        webupdate/src/md5.cpp
        webupdate/src/stdactions.cpp
        webupdate/src/versionrange.cpp
        webupdate/src/webupdate.cpp
        webupdate/src/webupdatectrl.cpp
    )
    SET(UPDATER_SRCS
    	webupdate/app/webapp.cpp
    	webupdate/app/webupdatedlg.cpp
    	webupdate/app/app.rc
    	webupdate/app/app.xpm
    	webupdate/app/www.xpm
    )
    INCLUDE_DIRECTORIES(
        ${INCLUDE_DIRECTORIES}
        webupdate/include
        webupdate/app/
    )
    ADD_LIBRARY(webupdate STATIC ${WEBUPDATE_SRCS})
    TARGET_LINK_LIBRARIES(webupdate ${wxWidgets_LIBRARIES})

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
    ADD_EXECUTABLE(DDPS-Updater ${GUI_TYPE} ${UPDATER_SRCS}) 
    TARGET_LINK_LIBRARIES(DDPS-Updater webupdate ${wxWidgets_LIBRARIES})

ENDIF(${UPDATER} MATCHES ON)

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
ADD_EXECUTABLE(DDPS ${GUI_TYPE} ${SRCS} ${HDRS})
TARGET_LINK_LIBRARIES(DDPS ${wxWidgets_LIBRARIES} ${DDPS_LIBS})
