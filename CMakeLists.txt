PROJECT( DDPS )

CMAKE_MINIMUM_REQUIRED(VERSION 2.4)

SET(DDPS_VERSION "1.0")
SET(CMAKE_FIND_LIBRARY_PREFIXES "")
SET(CMAKE_FIND_LIBRARY_SUFFIXES ".lib")
SET(wxWidgets_USE_LIBS base core net)


OPTION(COMMUNITY_PORTAL "Add Community Support" ON)
OPTION(USER_UPLOAD "Add User Upload capabilities" ON)
OPTION(BUILTIN_BROWSER "Add the Built-in Browser Support" ON)

SET(NEWSPAGE http://coreyb.homelinux.org/contentmanager/news CACHE STRING "Set the URL for Newspage")
SET(HOMEPAGE http://coreyb.homelinux.org/contentmanager CACHE STRING "Set the URL for Homepage")
SET(SUPPORTPAGE http://coreyb.homelinux.org/contentmanager/support CACHE STRING "Set the URL for Supportpage")
SET(COMMUNITYPAGE http://coreyb.homelinux.org/contentmanager/community CACHE STRING "Set the URL for Community Portal")

CONFIGURE_FILE(${CMAKE_SOURCE_DIR}/config.h.cmake
	${CMAKE_BINARY_DIR}/config.h ESCAPE_QUOTES)

SET(SRCS 
	AppMain.cpp
	AppMenu.cpp
	AppLogin.cpp
	BrowserEmbed.cpp
	TransferManager.cpp
	SettingsDialog.cpp
)

SET(HDRS
	enum.h
	common.h
	AppMain.h
	AppMenu.h
	AppLogin.h
	BrowserEmbed.h
	TransferManager.h
	SettingsDialog.h
)

FIND_PACKAGE(wxWidgets)

IF(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
	#MESSAGE("Using wxWebKitCtrl instead of wxMoz")
ELSE(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
	SET(USE_WXMOZ shipped CACHE SRING "Select system or shipped wxMozilla library")
	IF(${USE_WXMOZ} MATCHES "shipped")
		SUBDIRS(wxMoz)
		INCLUDE_DIRECTORIES(wxMoz)
		SET(wxMoz_LIB wxMoz)
	ELSE(${USE_WXMOZ} MATCHES "shipped")
		INCLUDE( ${CMAKE_ROOT}/Modules/UsePkgConfig.cmake )
		PKGCONFIG(wxmozilla WXMOZ_INCLUDE_DIR WXMOZ_LINK_DIR WXMOZ_LINK_FLAGS WXMOZ_CFLAGS)
		INCLUDE_DIRECTORIES(
			${WXMOZ_INCLUDE_DIR}
		)
		LINK_DIRECTORIES(
			${WXMOZ_LINK_DIR}
		)
		SET(wxMoz_LIB "")
	ENDIF(${USE_WXMOZ} MATCHES "shipped")
ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")

SET(CMAKE_EXE_LINKER_FLAGS ${CMAKE_EXE_LINKER_FLAGS} ${WXMOZ_LINK_FLAGS})
 
IF(wxWidgets_FOUND)

	INCLUDE(
		${wxWidgets_USE_FILE}
	)

	INCLUDE_DIRECTORIES(
		${INCLUDE_DIRECTORIES}
		${CMAKE_SOURCE_DIR}
		${CMAKE_BINARY_DIR}
		${wxWidgets_INCLUDE_DIRS}
	)
	IF(WIN32)
		SET(GUI_TYPE WIN32)
		SET(SRCS ${SRCS} ${CMAKE_SOURCE_DIR}/contrib/ddps.rc)
		
		INCLUDE_DIRECTORIES(
			${INCLUDE_DIRECTORIES}
			${CMAKE_SOURCE_DIR}/contrib/includes
			"C:\\libtorrent-0.13\\zlib"
			"C:\\libtorrent-0.13\\include"
			"C:\\libtorrent-0.13\\include\\libtorrent"
			"C:\\boost_1_35_0"
			"C:\\wxMozilla"
		)
		LINK_DIRECTORIES(
			${LINK_DIRECTORIES}
			"C:\\wxMozilla\\mozilla\\lib"
			"C:\\wxMozilla\\build\\msw\\DLL\ Release\ Monolithic\ WX_PYTHON_0"
			"C:\\libtorrent-0.13\\bin\\msvc-7.1\\release\\boost-source\\character-set-unicode\\threading-multi\\upnp-logging-on"
		)
		LINK_LIBRARIES(
			#libtorrent.lib
			embed_base_s.lib
			xpcom.lib
			xul.lib
			profdirserviceprovider_s.lib
			nspr4.lib
			plc4.lib
			plds4.lib
			wxbase28.lib
			wxbase28_net.lib
			wxbase28_xml.lib
			wxmsw28_adv.lib
			wxmsw28_aui.lib
			wxmsw28_core.lib
			wxmsw28_html.lib
			wxmsw28_media.lib
			wxmsw28_qa.lib
			wxmsw28_richtext.lib
			wxmsw28_xrc.lib
			wxtiff.lib
			wxjpeg.lib
			wxpng.lib
			wxzlib.lib
			wxregex.lib
			wxexpat.lib
			wxmozilla_lib.lib
		)
		#SET(CMAKE_CONFIGURATION_TYPES Release)
	ELSE(WIN32)
		IF(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
			SET(MACOSX_BUNDLE_INFO_STRING "")
			SET(MACOSX_BUNDLE_ICON_FILE "${CMAKE_SOURCE_DIR}/contrib/ddps.icns")
			SET(MACOSX_BUNDLE_GUI_IDENTIFIER "")
			SET(MACOSX_BUNDLE_LONG_VERSION_STRING "")
			SET(MACOSX_BUNDLE_BUNDLE_NAME "${PROJECT_NAME}")
			SET(MACOSX_BUNDLE_SHORT_VERSION_STRING "")
			SET(MACOSX_BUNDLE_BUNDLE_VERSION "${DDPS_VERSION}")
			SET(MACOSX_BUNDLE_COPYRIGHT "Copyright 2008 Sean Nelson, Corey Brown, Joshua Barron, Adam Troemne")
			#SET_SOURCE_FILES_PROPERTIES(apple1_aux1 PROPERTIES MACOSX_PACKAGE_LOCATION MacOSX)
			#SET_SOURCE_FILES_PROPERTIES(apple1_res1 PROPERTIES MACOSX_PACKAGE_LOCATION Resources)
			SET(GUI_TYPE MACOSX_BUNDLE)
		ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
	ENDIF(WIN32)

	ADD_EXECUTABLE(DDPS ${GUI_TYPE} ${SRCS} ${HDRS})
	TARGET_LINK_LIBRARIES(DDPS ${wxMoz_LIB} ${wxWidgets_LIBRARIES})
 
ELSE(wxWidgets_FOUND)
	MESSAGE("wxWidgets not found!")
ENDIF(wxWidgets_FOUND)
