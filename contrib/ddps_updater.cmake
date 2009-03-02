IF(${UPDATER} MATCHES ON)
    #SET(CMAKE_EXE_LINKER_FLAGS ${CMAKE_EXE_LINKER_FLAGS} ${CURL_LDFLAGS} -DWXUSINGDLL)
	#ADD_DEFINITIONS(-DWXUSINGDLL)
    SET(WEBUPDATE_SRCS
        webupdate/src/checkedlistctrl.cpp
        webupdate/src/download.cpp
        webupdate/src/installer.cpp
        webupdate/src/md5.cpp
        webupdate/src/stdactions.cpp
        webupdate/src/versionrange.cpp
        webupdate/src/webupdate.cpp
        webupdate/src/webupdatectrl.cpp
    )
    SET(UPDATER_SRCS
    	webupdate/app/webapp.cpp
    	webupdate/app/webupdatedlg.cpp
    	webupdate/app/app.rc
    	webupdate/app/app.xpm
    	webupdate/app/www.xpm
    )
    INCLUDE_DIRECTORIES(
        ${INCLUDE_DIRECTORIES}
        webupdate/include
        webupdate/app/
    )
    ADD_LIBRARY(webupdate SHARED ${WEBUPDATE_SRCS})
    TARGET_LINK_LIBRARIES(webupdate ${wxWidgets_LIBRARIES})

    IF(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
        SET(MACOSX_EXTRAS_UPDATE webupdate/libwebupdate.dylib)
        SET(MACOSX_BUNDLE_INFO_STRING "")
        #SET(MACOSX_BUNDLE_ICON_FILE "${CMAKE_SOURCE_DIR}/contrib/ddps-update.icns")
        SET(MACOSX_BUNDLE_GUI_IDENTIFIER "")
        SET(MACOSX_BUNDLE_LONG_VERSION_STRING "")
        SET(MACOSX_BUNDLE_BUNDLE_NAME "${PROJECT_NAME}-Updater")
        SET(MACOSX_BUNDLE_SHORT_VERSION_STRING "")
        SET(MACOSX_BUNDLE_BUNDLE_VERSION "${DDPS_UPDATE_VERSION}")
        SET(MACOSX_BUNDLE_COPYRIGHT "Copyright 2008 Sean Nelson")
        #SET_SOURCE_FILES_PROPERTIES(${MACOSX_EXTRAS_UPDATE} PROPERTIES MACOSX_PACKAGE_LOCATION MacOS)
    ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    ADD_EXECUTABLE(DDPS-Updater ${GUI_TYPE} ${UPDATER_SRCS}) 
    TARGET_LINK_LIBRARIES(DDPS-Updater webupdate ${wxWidgets_LIBRARIES})

ENDIF(${UPDATER} MATCHES ON)
