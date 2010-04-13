IF(${HTTP_DOWNLOADER} MATCHES ON)
    SET(SRCS ${SRCS} 
    	downloader/HttpManager.cpp
    )
    SET(HDRS ${HDRS} 
    	downloader/HttpManager.h
    )
ENDIF(${HTTP_DOWNLOADER} MATCHES ON)
