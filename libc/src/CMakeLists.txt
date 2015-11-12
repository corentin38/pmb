find_package( LibXml2 REQUIRED )
message( STATUS LIBXML2_FOUND = ${LIBXML2_FOUND} )
find_package( LibXslt REQUIRED )
message( STATUS LIBXSLT_FOUND = ${LIBXSLT_FOUND} )

include_directories( ${LIBXML2_INCLUDE_DIR} ${CMAKE_SOURCE_DIR}/libc/include )

remove_definitions( -Werror -Weffc++ -std=c++11 )

add_library( post post.c )
target_link_libraries( post ${LIBXML2_LIBRARIES} )

