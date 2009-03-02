IF(${DOWNLOADER} MATCHES ON)
	FIND_PACKAGE( Boost 1.35 COMPONENTS filesystem thread system )
	INCLUDE_DIRECTORIES(${INCLUDE_DIRECTORIES} ${Boost_INCLUDE_DIR})

    SET(SRCS ${SRCS} 
    	TransferCommon.cpp
    	TransferManager.cpp
    	TransferManagerList.cpp
    	TransferTimer.cpp
    )
    SET(HDRS ${HDRS} 
    	TransferCommon.h
    	TransferManager.h
    	TransferManagerList.h
    	TransferTimer.h
    )
ENDIF(${DOWNLOADER} MATCHES ON)
