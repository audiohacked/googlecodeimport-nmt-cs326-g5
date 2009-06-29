IF(${CHAT_ENABLED} MATCHES ON)
include( FindZLIB )
include( CheckFunctionExists )

check_function_exists( setsockopt SETSOCKOPT_EXISTS )

if( SETSOCKOPT_EXISTS )
        write_file( ${CMAKE_CURRENT_SOURCE_DIR}/gloox/config.h "#define HAVE_SETSOCKOPT 1")
endif( SETSOCKOPT_EXISTS )

if( ZLIB_FOUND )
    set( LIBS ${LIBS} ${ZLIB_LIBRARIES} )
    set( INCLUDE_DIRS ${INCLUDE_DIRS} ${ZLIB_INCLUDE_DIR} )
    write_file( ${CMAKE_CURRENT_SOURCE_DIR}/gloox/config.h "#define HAVE_ZLIB 1" APPEND )
endif( ZLIB_FOUND)

file( GLOB gloox_SRCS gloox/src/*.cpp )

INCLUDE_DIRECTORIES(
	${INCLUDE_DIRECTORIES}
	gloox/src
)

add_library( gloox ${gloox_SRCS} )
target_link_libraries( gloox ${LIBS} )

SET(gloox_LIB gloox)
SET(DDPS_LIBS ${DDPS_LIBS} ${gloox_LIB})
ENDIF(${CHAT_ENABLED} MATCHES ON)
