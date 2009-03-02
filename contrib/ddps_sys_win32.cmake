IF(WIN32)
	SET(GUI_TYPE WIN32)
	#SET(LIBS ${LIBS} wsock32.lib crypt32.lib secur32.lib dnsapi.lib)

	#SET(CMAKE_EXE_LINKER_FLAGS ${CMAKE_EXE_LINKER_FLAGS} -DWIN32)
	#ADD_DEFINITIONS(-DWIN32)

	#SET(SRCS ${SRCS} ${CMAKE_SOURCE_DIR}/contrib/ddps.rc)
	#SET(SYS_WIN32_LIBS comctl32.lib rpcrt4.lib winmm.lib advapi32.lib wsock32.lib)
	#SET(DDPS_LIBS ${DDPS_LIBS} ${SYS_WIN32_LIBS})
	#IF(MSVC)
	#	# msvc2005 deprecated warnings
	#	ADD_DEFINITIONS(-D_CRT_SECURE_NO_DEPRECATE)
	#	ADD_DEFINITIONS(-D_CRT_NONSTDC_NO_DEPRECATE)
	#	ADD_DEFINITIONS(-Zc:wchar_t-)
	#	# calm mdown msvc
	#	ADD_DEFINITIONS(-wd4251) # 'identifier' : class 'type' needs to have dll-interface to be used by clients of class 'type2'
	#	ADD_DEFINITIONS(-wd4275) # non  DLL-interface classkey 'identifier' used as base for DLL-interface classkey 'identifier'
	#	ADD_DEFINITIONS(-wd4309) # 'conversion' : truncation of constant value
	#	ADD_DEFINITIONS(-wd4503) # decorated name length exceeded
	#	ADD_DEFINITIONS(-wd4786) # identifier was truncated to '255' characters in the debug information
	#ENDIF(MSVC)
ENDIF(WIN32)
