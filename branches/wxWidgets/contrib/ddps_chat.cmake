IF(${CHAT_ENABLED} MATCHES ON)
	ADD_SUBDIRECTORY( gloox )
    
	SET(SRCS ${SRCS}
		ChatCommon.cpp
		ChatConnection.cpp
		ChatConnectionThread.cpp
		ChatMessage.cpp
		ChatRoster.cpp
		ChatWindow.cpp
		ChatRosterData.cpp
	)
	SET(HDRS ${HDRS}
		ChatCommon.h
		ChatConnection.h
		ChatConnectionThread.h
		ChatMessage.h
		ChatRoster.h
		ChatWindow.h
		ChatRosterData.h
	)
	INCLUDE_DIRECTORIES(
		${INCLUDE_DIRECTORIES}
		gloox/src
	)
	SET(gloox_LIB gloox)
    SET(DDPS_LIBS ${DDPS_LIBS} ${gloox_LIB})
ENDIF(${CHAT_ENABLED} MATCHES ON)
