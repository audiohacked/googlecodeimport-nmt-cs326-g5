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

    SET(CMAKE_EXE_LINKER_FLAGS ${CMAKE_EXE_LINKER_FLAGS} ${WXMOZ_LDFLAGS})
ENDIF(${BUILTIN_BROWSER} MATCHES ON)