PROJECT( mozembed )

CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

SET(BUILD_SHARED_LIBS ON)
SET(wxWidgets_USE_LIBS base core net)

SET(mozembed_SRCS
	common/embed.cpp
	common/WebBrowserChrome.cpp
	common/EmbeddingSetup.cpp
	common/ContentListener.cpp
	wx/wxMozView.cpp
	wx/wxMozProfile.cpp 
)

SET(mozebmed_HDRS
	common/embed.h
)

FIND_PACKAGE(wxWidgets)
#PKG_CHECK_MODULES(MOZ libxul libxul-embedding-unstable mozilla-js gtk+2.0)

IF(WIN32)
	SET(XPCOM_INCLUDE_DIRS "C:\\wxMozilla\\mozilla\\include")
	SET(XPCOM_LIBRARY_DIRS "C:\\wxMozilla\\mozilla\\lib")
ELSE(WIN32)
#	IF(${MOZ_USE} MATCHES "FF")
#		PKG_CHECK_MODULES(XPCOM firefox-xpcom)
#	ENDIF(${MOZ_USE} MATCHES "FF")
	
#	IF(${MOZ_USE} MATCHES "XUL")
		PKG_CHECK_MODULES(XPCOM libxul)
#	ENDIF(${MOZ_USE} MATCHES "XUL")

#	IF(${MOZ_USE} MATCHES "MOZ")
#		PKG_CHECK_MODULES(XPCOM mozilla-xpcom)
#	ENDIF(${MOZ_USE} MATCHES "MOZ")

	FIND_PACKAGE(GTK)
#	PKG_CHECK_MODULES(GTK gtk+-2.0)
ENDIF(WIN32)

IF(wxWidgets_FOUND)
	
	ADD_DEFINITIONS( -DMOZILLA_INTERNAL_API -DMOZILLA_HOME='"${XPCOM_PREFIX}"' )
	
	IF(WIN32)
		LINK_LIBRARIES(embed_base_s)
	ENDIF(WIN32)


#	IF(UNIX)
#		IF(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
#			LINK_LIBRARIES()
#		ELSE(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
#			LINK_LIBRARIES(gtkembedmoz)
#		ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
#	ENDIF(UNIX)
	

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
		${XPCOM_LIBRARIES}
		#xpcom
		#nspr4
		#plds4
		#plc4
	)
	
	ADD_LIBRARY(mozebmed ${mozebmed_SRCS} ${mozebmed_HDRS})
	TARGET_LINK_LIBRARIES(mozebmed ${XPCOM_LDFLAGS} ${wxWidgets_LIBRARIES} ${GTK_LDFLAGS})

ELSE(wxWidgets_FOUND)
	MESSAGE("wxWidgets not found!")
ENDIF(wxWidgets_FOUND)

#MOZ_CFLAGS=-DMOZ_DLL_SUFFIX="\".so\"" `pkg-config --cflags libxul libxul-embedding-unstable mozilla-js`
#MOZ_LIBS=`pkg-config --libs libxul libxul-embedding-unstable mozilla-js`
#CFLAGS=-fno-rtti -I../common $(MOZ_CFLAGS) `wx-config --unicode --cxxflags` `pkg-config --cflags gtk+-2.0` 
#LDFLAGS=`wx-config --libs core` $(MOZ_LIBS)
