include_directories( 
  ${CMAKE_SOURCE_DIR}/lib/bin/flate
  SYSTEM ${Boost_INCLUDE_DIRS}
  ${CMAKE_SOURCE_DIR}/lib/include
  ${CMAKE_SOURCE_DIR}/lib/gen
)

#add_definitions( -Werror -Weffc++ -std=c++11 )
add_definitions( -Weffc++ -std=c++11 )

find_library( FLATE libflate.a PATHS ${CMAKE_SOURCE_DIR}/lib/bin/flate )

# Utils library (perso)
add_library( utils
  boost_utils.cpp
  simple_logger.cpp
)

target_link_libraries( utils ${Boost_LIBRARIES} )

# CPP Markdown (stolen)
add_library(cppmarkdown
  markdown.cpp
  markdown-tokens.cpp
)
  
target_link_libraries(cppmarkdown PUBLIC ${Boost_LIBRARIES})

# BLOG main library
add_library( blog
  factory_blog.cpp
  blog_local.cpp
  persistor_blog.cpp
  controller_blog.cpp
  persistable_blog.cpp
  generator.cpp
  configuration_blog.cpp
)

target_link_libraries( blog 
  utils
  cppmarkdown
  ${CMAKE_THREAD_LIBS_INIT}
  ${Boost_LIBRARIES}
  ${FLATE}
)

