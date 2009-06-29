IF(${CHAT_ENABLED} MATCHES ON)
	SET(SRCS ${SRCS}
		chat/ChatBackend.cpp
#		chat/ChatConnection.cpp
#		chat/ChatConnectionThread.cpp
#		chat/ChatMessage.cpp
		chat/ChatRoster.cpp
		chat/ChatWindow.cpp
		chat/ChatRosterData.cpp
	)
	SET(HDRS ${HDRS}
		chat/ChatBackend.h
#		chat/ChatConnection.h
#		chat/ChatConnectionThread.h
#		chat/ChatMessage.h
		chat/ChatRoster.h
		chat/ChatWindow.h
		chat/ChatRosterData.h
	)
ENDIF(${CHAT_ENABLED} MATCHES ON)
