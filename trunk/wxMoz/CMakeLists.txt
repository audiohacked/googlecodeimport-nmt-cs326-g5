PROJECT(wxMoz)

SET(wxWidgets_USE_LIBS base core net)

FIND_PACKAGE(wxWidgets)
FIND_PACKAGE(GTK)

INCLUDE( ${CMAKE_ROOT}/Modules/UsePkgConfig.cmake )

ADD_DEFINITIONS( -DMOZILLA_INTERNAL_API -DMOZILLA_HOME='"${XPCOM_LINK_DIR}"' )

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

PKGCONFIG(xulrunner-xpcom XPCOM_INCLUDE_DIR XPCOM_LINK_DIR XPCOM_LINK_FLAGS XPCOM_CFLAGS)
PKGCONFIG(firefox-xpcom XPCOM_INCLUDE_DIR XPCOM_LINK_DIR XPCOM_LINK_FLAGS XPCOM_CFLAGS)
PKGCONFIG(gtk+-2.0 GTK_INCLUDE_DIR GTK_LINK_DIR GTK_LINK_FLAGS GTK_CFLAGS)

IF(wxWidgets_FOUND)
	SET(CMAKE_CXX_FLAGS "${XPCOM_CFLAGS} ${GTK_CFLAGS}")
	INCLUDE(${wxWidgets_USE_FILE})
	INCLUDE_DIRECTORIES(
		${wxWidgets_INCLUDE_DIRS}
		${GTK_INCLUDE_DIR}
		${XPCOM_INCLUDE_DIR}		
		${XPCOM_INCLUDE_DIR}/unix
		${XPCOM_INCLUDE_DIR}/dom
		${XPCOM_INCLUDE_DIR}/windowwatcher
		${XPCOM_INCLUDE_DIR}/webbrowserpersist
		${XPCOM_INCLUDE_DIR}/appcomps
		${XPCOM_INCLUDE_DIR}/find
		${XPCOM_INCLUDE_DIR}/txtsvc
		${XPCOM_INCLUDE_DIR}/docshell
		${XPCOM_INCLUDE_DIR}/shistory 
		${XPCOM_INCLUDE_DIR}/webshell
		${XPCOM_INCLUDE_DIR}/gfx
		${XPCOM_INCLUDE_DIR}/necko 
		${XPCOM_INCLUDE_DIR}/widget 
		${XPCOM_INCLUDE_DIR}/content
		${XPCOM_INCLUDE_DIR}/layout 
		${XPCOM_INCLUDE_DIR}/browser
		${XPCOM_INCLUDE_DIR}/webbrwsr
		${XPCOM_INCLUDE_DIR}/uconv 
		${XPCOM_INCLUDE_DIR}/embed_base 
		${XPCOM_INCLUDE_DIR}/uriloader 
		${XPCOM_INCLUDE_DIR}/editor 
		${XPCOM_INCLUDE_DIR}/commandhandler 
		${XPCOM_INCLUDE_DIR}/composer
		${XPCOM_INCLUDE_DIR}/pref 
		${XPCOM_INCLUDE_DIR}/profdirserviceprovider
		${XPCOM_INCLUDE_DIR}/xpcom
		${XPCOM_INCLUDE_DIR}/nspr
		${XPCOM_INCLUDE_DIR}/profile
		${XPCOM_INCLUDE_DIR}/string
	)

	LINK_DIRECTORIES(
		${XPCOM_LINK_DIR}
	)
	
	LINK_LIBRARIES(
		gtkembedmoz
		xpcom
		nspr4
		plds4
		plc4
	)
	
	ADD_LIBRARY(wxMoz ${wxMoz_SRCS} ${wxMoz_HDRS})
	TARGET_LINK_LIBRARIES(wxMoz ${XPCOM_LINK_FLAGS}
		${wxWidgets_LIBRARIES} ${GTK_LINK_FLAGS})

	ELSE(wxWidgets_FOUND)
		MESSAGE("wxWidgets not found!")
	ENDIF(wxWidgets_FOUND)
