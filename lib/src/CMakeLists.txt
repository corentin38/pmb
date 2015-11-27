include_directories( 
  ${LIBXML2_INCLUDE_DIR}
  ${Boost_INCLUDE_DIRS}
  ${CMAKE_SOURCE_DIR}/libc/include 
  ${CMAKE_SOURCE_DIR}/lib/include
  ${CMAKE_SOURCE_DIR}/lib/gen
)

#add_definitions( -Werror -Weffc++ -std=c++11 )
add_definitions( -Weffc++ -std=c++11 )

add_library( utils boost_utils.cpp simple_logger.cpp )
target_link_libraries( utils ${Boost_LIBRARIES} )

add_library( blog factory_blog.cpp blog_local.cpp persistor_blog.cpp )
target_link_libraries( blog post utils ${CMAKE_THREAD_LIBS_INIT} ${Boost_LIBRARIES} )
