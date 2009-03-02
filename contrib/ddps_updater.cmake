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
    ADD_LIBRARY(webupdate ${WEBUPDATE_SRCS})
    TARGET_LINK_LIBRARIES(webupdate ${wxWidgets_LIBRARIES})

    ADD_EXECUTABLE(DDPS-Updater ${GUI_TYPE} ${UPDATER_SRCS}) 
    TARGET_LINK_LIBRARIES(DDPS-Updater webupdate ${wxWidgets_LIBRARIES})

ENDIF(${UPDATER} MATCHES ON)
