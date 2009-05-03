IF(${DOWNLOADER} MATCHES ON)
	SET(SRCS ${SRCS} 
		TransferManager.cpp
		TransferTimer.cpp
	)
	SET(HDRS ${HDRS} 
		TransferManager.h
		TransferTimer.h
	)
ENDIF(${DOWNLOADER} MATCHES ON)
