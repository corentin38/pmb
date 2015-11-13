include_directories( 
  ${LIBXML2_INCLUDE_DIR}
  ${Boost_INCLUDE_DIRS}
  ${CMAKE_SOURCE_DIR}/libc/include 
  ${CMAKE_SOURCE_DIR}/lib/include
  ${CMAKE_SOURCE_DIR}/lib/gen
)

add_definitions( -Werror -Weffc++ -std=c++11 )

add_library( blog factory_blog.cpp blog_local.cpp )
target_link_libraries( blog post ${Boost_LIBRARIES} )
