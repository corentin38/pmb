find_package( LibXml2 REQUIRED )
message( STATUS LIBXML2_FOUND = ${LIBXML2_FOUND} )

include_directories( ${LIBXML2_INCLUDE_DIR} ${CMAKE_SOURCE_DIR}/blog/include )

#add_library( blog blog.cpp )
add_library( blog  )
