include_directories( 
  ${CMAKE_SOURCE_DIR}/lib/flate
  SYSTEM ${Boost_INCLUDE_DIRS}
  ${CMAKE_SOURCE_DIR}/include
)

#add_definitions( -Werror -Weffc++ -std=c++11 )
add_definitions( -Weffc++ -std=c++11 )

# Utils library (perso)
add_library( utils
  boost_utils.cpp
  simple_logger.cpp
)

set_property(TARGET utils PROPERTY COMPILE_FLAGS "-fPIC")

target_link_libraries( utils ${Boost_LIBRARIES} )

# CPP Markdown (stolen)
add_library(cppmarkdown
  markdown.cpp
  markdown-tokens.cpp
)
  
SET_TARGET_PROPERTIES(cppmarkdown PROPERTIES COMPILE_FLAGS "-fPIC")
target_link_libraries(cppmarkdown PUBLIC ${Boost_LIBRARIES})
