find_package( LibXml2 REQUIRED )
message( STATUS LIBXML2_FOUND = ${LIBXML2_FOUND} )

include_directories( ${LIBXML2_INCLUDE_DIR} ${CMAKE_SOURCE_DIR}/lib/include )

add_library( post post.c )
target_link_libraries( post ${LIBXML2_LIBRARIES} )

add_library( blog blog.cpp )
target_link_libraries( blog post )
