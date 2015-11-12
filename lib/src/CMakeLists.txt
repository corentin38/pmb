include_directories( ${LIBXML2_INCLUDE_DIR} ${CMAKE_SOURCE_DIR}/lib/include )

add_library( blog factory_blog.cpp blog_local.cpp )
target_link_libraries( blog post )
