IF(${HTTP_DOWNLOADER} MATCHES ON)
    SET(SRCS ${SRCS} 
    	HttpManager.cpp
    )
    SET(HDRS ${HDRS} 
    	HttpManager.h
    )
ENDIF(${HTTP_DOWNLOADER} MATCHES ON)
