IF(${DOWNLOADER} MATCHES ON)
	SET(SRCS ${SRCS} 
		downloader/TransferManager.cpp
		downloader/TransferManagerData.cpp
		downloader/TransferTimer.cpp
	)
	SET(HDRS ${HDRS} 
		downloader/TransferManager.h
		downloader/TransferManagerData.h
		downloader/TransferTimer.h
	)
ENDIF(${DOWNLOADER} MATCHES ON)
