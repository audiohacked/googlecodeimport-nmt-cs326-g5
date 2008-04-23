PROJECT( sApp )

CMAKE_MINIMUM_REQUIRED(VERSION 2.4)

SET(sAPP_VERSION "1.0")
SET(CMAKE_FIND_LIBRARY_PREFIXES "")
SET(CMAKE_FIND_LIBRARY_SUFFIXES ".lib")
SET(wxWidgets_USE_LIBS base core net)

OPTION(COMMUNITY_PORTAL "Add Community Support" ON)
OPTION(USER_UPLOAD "Add User Upload capabilities" ON)
OPTION(BUILTIN_BROWSER "Add the Built-in Browser Support" ON)

CONFIGURE_FILE(${CMAKE_SOURCE_DIR}/config.h.cmake
	${CMAKE_BINARY_DIR}/config.h)

SET(SRCS 
	AppMain.cpp
	AppMenu.cpp
	BrowserEmbed.cpp
)

SET(HDRS
	enum.h
	AppMain.h
	AppMenu.h
	BrowserEmbed.h
)


FIND_PACKAGE(wxWidgets)

INCLUDE( ${CMAKE_ROOT}/Modules/UsePkgConfig.cmake )
PKGCONFIG(wxmozilla WXMOZ_INCLUDE_DIR WXMOZ_LINK_DIR WXMOZ_LINK_FLAGS WXMOZ_CFLAGS)
SET(CMAKE_EXE_LINKER_FLAGS ${CMAKE_EXE_LINKER_FLAGS} ${WXMOZ_LINK_FLAGS})
 
IF(wxWidgets_FOUND)

	INCLUDE(
		${wxWidgets_USE_FILE}
	)

	INCLUDE_DIRECTORIES(
		${CMAKE_SOURCE_DIR}
		${CMAKE_BINARY_DIR}
		${wxWidgets_INCLUDE_DIRS}
		${WXMOZ_INCLUDE_DIR}
	)
	LINK_DIRECTORIES(
		${WXMOZ_LINK_DIR}
	)
	IF(WIN32)
		SET(GUI_TYPE WIN32)
		SET(SRCS ${SRCS} ${CMAKE_SOURCE_DIR}/contrib/wxSean.rc)
		
		INCLUDE_DIRECTORIES(
			${INCLUDE_DIRECTORIES}
			${CMAKE_SOURCE_DIR}/contrib/includes
		)
		LINK_DIRECTORIES(
			${LINK_DIRECTORIES}
			"C:\\wxMozilla\\mozilla\\lib"
			"C:\\wxMozilla\\build\\msw\\DLL\ Release\ Monolithic\ WX_PYTHON_0"
		)
		LINK_LIBRARIES(
			embed_base_s.lib
			xpcom.lib
			xul.lib
			profdirserviceprovider_s.lib
			nspr4.lib
			plc4.lib
			plds4.lib
			wxmsw28_core.lib
			wxbase28.lib
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
			SET(MACOSX_BUNDLE_ICON_FILE "${CMAKE_SOURCE_DIR}/contrib/wxSean.icns")
			SET(MACOSX_BUNDLE_GUI_IDENTIFIER "")
			SET(MACOSX_BUNDLE_LONG_VERSION_STRING "")
			SET(MACOSX_BUNDLE_BUNDLE_NAME "${PROJECT_NAME}")
			SET(MACOSX_BUNDLE_SHORT_VERSION_STRING "")
			SET(MACOSX_BUNDLE_BUNDLE_VERSION "${sAPP_VERSION}")
			SET(MACOSX_BUNDLE_COPYRIGHT "Copyright 2008 Sean Nelson")
			#SET_SOURCE_FILES_PROPERTIES(apple1_aux1 PROPERTIES MACOSX_PACKAGE_LOCATION MacOSX)
			#SET_SOURCE_FILES_PROPERTIES(apple1_res1 PROPERTIES MACOSX_PACKAGE_LOCATION Resources)
			SET(GUI_TYPE MACOSX_BUNDLE)
		ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
	ENDIF(WIN32)

	ADD_EXECUTABLE(sApp ${GUI_TYPE} ${SRCS} ${HDRS})
	TARGET_LINK_LIBRARIES(sApp ${wxWidgets_LIBRARIES})
 
ELSE(wxWidgets_FOUND)
	MESSAGE("wxWidgets not found!")
ENDIF(wxWidgets_FOUND)
