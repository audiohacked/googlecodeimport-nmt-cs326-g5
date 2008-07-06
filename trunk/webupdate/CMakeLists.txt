PROJECT (webupdate)

SET(SRCS
	src/checkedlistctrl.cpp
	src/download.cpp
	src/installer.cpp
	src/md5.cpp
	src/stdactions.cpp
	src/versionrange.cpp
	src/webupdate.cpp
	src/webupdatectrl.cpp
	)

SET(wxWidgets_USE_LIBS base core net xml)

FIND_PACKAGE(wxWidgets)

IF(wxWidgets_FOUND)
	INCLUDE( ${wxWidgets_USE_FILE})
	INCLUDE_DIRECTORIES(
		${INCLUDE_DIRECTORIES}
		${wxWidgets_INCLUDE_DIRS}
		include
	)

	ADD_LIBRARY(webupdate ${SRCS})
	TARGET_LINK_LIBRARIES(webupdate ${wxWidgets_LIBRARIES})
ENDIF(wxWidgets_FOUND)