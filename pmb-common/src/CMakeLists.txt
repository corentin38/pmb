include_directories( 
  ${CMAKE_SOURCE_DIR}/lib/flate
  SYSTEM ${Boost_INCLUDE_DIRS}
  ${CMAKE_SOURCE_DIR}/include
)

#add_definitions( -Werror -Weffc++ -std=c++11 )
add_definitions( -Weffc++ -std=c++11 )

find_library( FLATE libflate.a PATHS ${CMAKE_SOURCE_DIR}/lib/flate )

# Utils library (perso)
add_library( utils
  boost_utils.cpp
  simple_logger.cpp
)

SET_TARGET_PROPERTIES(utils PROPERTIES COMPILE_FLAGS "-fPIC")
target_link_libraries( utils ${Boost_LIBRARIES} )

# CPP Markdown (stolen)
add_library(cppmarkdown
  markdown.cpp
  markdown-tokens.cpp
)
  
SET_TARGET_PROPERTIES(cppmarkdown PROPERTIES COMPILE_FLAGS "-fPIC")
target_link_libraries(cppmarkdown PUBLIC ${Boost_LIBRARIES})

# pmb-common library
add_library( ${PROJECT_NAME} SHARED
  factory_blog.cpp
  blog_local.cpp
  persistor_blog.cpp
  controller_blog.cpp
  persistable_blog.cpp
  generator.cpp
  configuration_blog.cpp
)

SET_TARGET_PROPERTIES(${PROJECT_NAME} PROPERTIES COMPILE_FLAGS "-fPIC")
target_link_libraries( ${PROJECT_NAME} 
  utils
  cppmarkdown
  ${Boost_LIBRARIES}
  ${FLATE}
)

