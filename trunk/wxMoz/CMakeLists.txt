PROJECT(wxMoz)

SET(wxWidgets_USE_LIBS base core net)

FIND_PACKAGE(wxWidgets)

SET(MOZ_USE FF CACHE STRING "Select browser base code: FF, XUL, MOZ")

INCLUDE( ${CMAKE_ROOT}/Modules/UsePkgConfig.cmake )

SET(wxMoz_SRCS
	cstmdlg.cpp
	wxMozillaBrowserChrome.cpp
	wxMozillaProtocolHandler.cpp
	helpers.cpp
	wxMozillaDialogs.cpp
	wxMozillaSettings.cpp
	wxMozillaBrowser.cpp		
	wxMozillaEvents.cpp		
	wxMozillaWindow.cpp
)

SET(wxMoz_HDRS
	cstmdlg.h
	wxMozillaBrowserChrome.h
	wxMozillaEvents.h
	helpers.h
	wxMozillaBrowserInterface.h
	wxMozillaProtocolHandler.h
	wxMozilla.h
	wxMozillaComponents.h
	wxMozillaSettings.h
	wxMozillaBrowser.h
	wxMozillaDialogs.h
	wxMozillaWindow.h
)
IF(WIN32)
	SET(XPCOM_INCLUDE_DIRS "C:\\wxMozilla\\mozilla\\include")
	SET(XPCOM_LIBRARY_DIRS "C:\\wxMozilla\\mozilla\\lib")
ELSE(WIN32)
	IF(${MOZ_USE} MATCHES "FF")
		PKG_CHECK_MODULES(XPCOM firefox-xpcom)
	ENDIF(${MOZ_USE} MATCHES "FF")
	
	IF(${MOZ_USE} MATCHES "XUL")
		PKG_CHECK_MODULES(XPCOM libxul)
	ENDIF(${MOZ_USE} MATCHES "XUL")

	IF(${MOZ_USE} MATCHES "MOZ")
		PKG_CHECK_MODULES(XPCOM mozilla-xpcom)
	ENDIF(${MOZ_USE} MATCHES "MOZ")

	FIND_PACKAGE(GTK)
#	PKG_CHECK_MODULES(GTK gtk+-2.0)
ENDIF(WIN32)

IF(wxWidgets_FOUND)
	
	ADD_DEFINITIONS( -DMOZILLA_INTERNAL_API -DMOZILLA_HOME='"${XPCOM_PREFIX}"' )
	
	IF(WIN32)
		LINK_LIBRARIES(embed_base_s)
	ENDIF(WIN32)


	IF(UNIX)
		IF(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
			LINK_LIBRARIES()
		ELSE(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
			LINK_LIBRARIES(gtkembedmoz)
		ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
	ENDIF(UNIX)
	

	SET(CMAKE_CXX_FLAGS "${XPCOM_CFLAGS} ${GTK_CFLAGS}")
	INCLUDE(${wxWidgets_USE_FILE})
	INCLUDE_DIRECTORIES(
		${wxWidgets_INCLUDE_DIRS}
		${GTK_INCLUDE_DIRS}
		${XPCOM_INCLUDE_DIRS}		
	)

	LINK_DIRECTORIES(
		${XPCOM_LIBRARY_DIRS}
	)

	LINK_LIBRARIES(
		${LINK_LIBRARIES}
		xpcom
		nspr4
		plds4
		plc4
	)
	
	ADD_LIBRARY(wxMoz ${wxMoz_SRCS} ${wxMoz_HDRS})
	TARGET_LINK_LIBRARIES(wxMoz ${XPCOM_LDFLAGS}
		${wxWidgets_LIBRARIES} ${GTK_LDFLAGS})

ELSE(wxWidgets_FOUND)
	MESSAGE("wxWidgets not found!")
ENDIF(wxWidgets_FOUND)
