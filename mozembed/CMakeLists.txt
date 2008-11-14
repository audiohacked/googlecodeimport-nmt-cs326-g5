PROJECT( mozembed )

CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

CMAKE_POLICY(SET CMP0005 NEW)
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

SET(mozembed_HDRS
	common/embed.h
)

FIND_PACKAGE(wxWidgets)

PKG_CHECK_MODULES(EMBED REQUIRED libxul libxul-embedding-unstable mozilla-js)
FIND_PACKAGE(GTK)

SET(mozembed_CFLAGS "${EMBED_CFLAGS_OTHER} ${GTK_CFLAGS_OTHER}" CACHE STRING "CXX Flags for mozembed")

IF(wxWidgets_FOUND AND EMBED_FOUND)
	SET(CMAKE_CXX_FLAGS "-fshort-wchar -DXPCOM_GLUE -DXP_UNIX -DJS_THREADSAFE")
	INCLUDE(${wxWidgets_USE_FILE})
	INCLUDE_DIRECTORIES(
		${wxWidgets_INCLUDE_DIRS}
		${GTK_INCLUDE_DIRS}
		${EMBED_INCLUDE_DIRS}
		common
		wx
	)

	LINK_DIRECTORIES(
		${LINK_DIRECTORIES}
		${EMBED_LIBRARY_DIRS}
	)

	LINK_LIBRARIES(
		${LINK_LIBRARIES}
		${EMBED_LIBRARIES}
	)
	
	ADD_LIBRARY(mozembed ${mozembed_SRCS} ${mozembed_HDRS})
	TARGET_LINK_LIBRARIES(mozembed ${EMBED_LDFLAGS} ${wxWidgets_LIBRARIES} ${GTK_LDFLAGS})

ELSE(wxWidgets_FOUND AND EMBED_FOUND)
	MESSAGE("wxWidgets not found!")
ENDIF(wxWidgets_FOUND AND EMBED_FOUND)
