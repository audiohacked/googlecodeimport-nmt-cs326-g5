IF(${DOWNLOADER} MATCHES ON)
    SET(CMAKE_EXE_LINKER_FLAGS ${CMAKE_EXE_LINKER_FLAGS} -DNDEBUG -DBUILDING_LIBCURL -DUSE_WINSOCK=1 -DWXUSINGDLL)
	#ADD_DEFINITIONS( -DNDEBUG -DBUILDING_LIBCURL -DUSE_WINSOCK=1 -DWXUSINGDLL)
	IF(WIN32)
		SET(WIN32_CURL_LIB wsock32.lib winmm.lib)
	ENDIF(WIN32)

	SET(DDPS_LIBS ${DDPS_LIBS} libcurl wxcurl)

    SET(SRCS ${SRCS} 
    	HttpManager.cpp
    	TransferCommon.cpp
    	TransferManager.cpp
    	TransferManagerList.cpp
    	TransferTimer.cpp
    )
    SET(HDRS ${HDRS} 
    	HttpManager.h
    	TransferCommon.h
    	TransferManager.h
    	TransferManagerList.h
    	TransferTimer.h
    )
	SET(CURL_SRCS
		wxCURL/thirdparty/curl/lib/base64.c
		wxCURL/thirdparty/curl/lib/connect.c
		wxCURL/thirdparty/curl/lib/content_encoding.c
		wxCURL/thirdparty/curl/lib/cookie.c
		wxCURL/thirdparty/curl/lib/dict.c
		wxCURL/thirdparty/curl/lib/easy.c
		wxCURL/thirdparty/curl/lib/escape.c
		wxCURL/thirdparty/curl/lib/file.c
		wxCURL/thirdparty/curl/lib/formdata.c
		wxCURL/thirdparty/curl/lib/ftp.c
		wxCURL/thirdparty/curl/lib/getenv.c
		wxCURL/thirdparty/curl/lib/getinfo.c
		wxCURL/thirdparty/curl/lib/gtls.c
		wxCURL/thirdparty/curl/lib/hash.c
		wxCURL/thirdparty/curl/lib/hostares.c
		wxCURL/thirdparty/curl/lib/hostasyn.c
		wxCURL/thirdparty/curl/lib/hostip.c
		wxCURL/thirdparty/curl/lib/hostip4.c
		wxCURL/thirdparty/curl/lib/hostip6.c
		wxCURL/thirdparty/curl/lib/hostsyn.c
		wxCURL/thirdparty/curl/lib/hostthre.c
		wxCURL/thirdparty/curl/lib/http.c
		wxCURL/thirdparty/curl/lib/http_chunks.c
		wxCURL/thirdparty/curl/lib/http_digest.c
		wxCURL/thirdparty/curl/lib/http_negotiate.c
		wxCURL/thirdparty/curl/lib/http_ntlm.c
		wxCURL/thirdparty/curl/lib/if2ip.c
		wxCURL/thirdparty/curl/lib/inet_ntop.c
		wxCURL/thirdparty/curl/lib/inet_pton.c
		wxCURL/thirdparty/curl/lib/krb4.c
		wxCURL/thirdparty/curl/lib/ldap.c
		wxCURL/thirdparty/curl/lib/llist.c
		wxCURL/thirdparty/curl/lib/md5.c
		wxCURL/thirdparty/curl/lib/memdebug.c
		wxCURL/thirdparty/curl/lib/mprintf.c
		wxCURL/thirdparty/curl/lib/multi.c
		wxCURL/thirdparty/curl/lib/netrc.c
		wxCURL/thirdparty/curl/lib/parsedate.c
		wxCURL/thirdparty/curl/lib/progress.c
		wxCURL/thirdparty/curl/lib/security.c
		wxCURL/thirdparty/curl/lib/select.c
		wxCURL/thirdparty/curl/lib/sendf.c
		wxCURL/thirdparty/curl/lib/share.c
		wxCURL/thirdparty/curl/lib/socks.c
		wxCURL/thirdparty/curl/lib/speedcheck.c
		wxCURL/thirdparty/curl/lib/splay.c
		wxCURL/thirdparty/curl/lib/ssh.c
		wxCURL/thirdparty/curl/lib/sslgen.c
		wxCURL/thirdparty/curl/lib/ssluse.c
		wxCURL/thirdparty/curl/lib/strdup.c
		wxCURL/thirdparty/curl/lib/strequal.c
		wxCURL/thirdparty/curl/lib/strerror.c
		wxCURL/thirdparty/curl/lib/strtok.c
		wxCURL/thirdparty/curl/lib/strtoofft.c
		wxCURL/thirdparty/curl/lib/telnet.c
		wxCURL/thirdparty/curl/lib/tftp.c
		wxCURL/thirdparty/curl/lib/timeval.c
		wxCURL/thirdparty/curl/lib/transfer.c
		wxCURL/thirdparty/curl/lib/url.c
		wxCURL/thirdparty/curl/lib/version.c
	)
	SET(WXCURL_SRCS
		wxCURL/src/base.cpp
		wxCURL/src/dav.cpp
		wxCURL/src/davtool.cpp
		wxCURL/src/dialog.cpp
		wxCURL/src/ftp.cpp
		wxCURL/src/ftpparse.cpp
		wxCURL/src/ftptool.cpp
		wxCURL/src/http.cpp
		wxCURL/src/panel.cpp
		wxCURL/src/telnet.cpp
		wxCURL/src/thread.cpp
		wxCURL/src/utils.cpp
	)
	
    INCLUDE_DIRECTORIES(
        ${INCLUDE_DIRECTORIES}
        wxCURL/thirdparty/curl/include
		wxCURL/thirdparty/curl/lib
        wxCURL/include
    )
	
	ADD_LIBRARY(libcurl ${CURL_SRCS})
    TARGET_LINK_LIBRARIES(libcurl ${WIN32_CURL_LIB})
	ADD_LIBRARY(wxcurl ${WXCURL_SRCS})
    TARGET_LINK_LIBRARIES(wxcurl ${wxWidgets_LIBRARIES} ${WIN32_CURL_LIB} libcurl)

    IF(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
        SET(MACOSX_EXTRAS
            ${MACOSX_EXTRAS} 
            wxCURL/libwxcurl.dylib
        )
    ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")

    SET(CMAKE_EXE_LINKER_FLAGS ${CMAKE_EXE_LINKER_FLAGS} ${CURL_LDFLAGS})
ENDIF(${DOWNLOADER} MATCHES ON)
