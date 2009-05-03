IF(${BUILTIN_BROWSER} MATCHES ON)
    SET(SRCS ${SRCS} 
    	BrowserEmbed.cpp
    )
    SET(HDRS ${HDRS} 
    	BrowserEmbed.h
    )
ENDIF(${BUILTIN_BROWSER} MATCHES ON)