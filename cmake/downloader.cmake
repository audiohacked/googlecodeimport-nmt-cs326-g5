IF(${DOWNLOADER} MATCHES ON)
	SET(SRCS ${SRCS} 
		TransferManager.cpp
		TransferManagerData.cpp
		TransferTimer.cpp
	)
	SET(HDRS ${HDRS} 
		TransferManager.h
		TransferManagerData.h
		TransferTimer.h
	)
ENDIF(${DOWNLOADER} MATCHES ON)
