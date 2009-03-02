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