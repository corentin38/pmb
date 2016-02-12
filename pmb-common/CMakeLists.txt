CMAKE_MINIMUM_REQUIRED( VERSION 2.8 )
project( pmb-common )

## MAKE SURE THIS POINTS TO PROPER RESOURCE FILES ################
set( TEMPLATE_RESOURCE ${CMAKE_SOURCE_DIR}/resources/page.tpl )
set( CONTENT_SAMPLE_RESOURCE ${CMAKE_SOURCE_DIR}/resources/content_sample.xml )
set( CONTENT_EMPTY_RESOURCE ${CMAKE_SOURCE_DIR}/resources/content_empty.xml )
set( BOOTSTRAP_RESOURCE ${CMAKE_SOURCE_DIR}/resources/dist )
set( CSS_RESOURCE ${CMAKE_SOURCE_DIR}/resources/blog.css )

configure_file( 
  ${CMAKE_SOURCE_DIR}/include/gen/blog_constants.hpp.in 
  ${CMAKE_SOURCE_DIR}/include/gen/blog_constants.hpp 
)
##################################################################

#add_definitions( -Wall -Wextra -Werror -Weffc++ -std=c++11 )
#add_definitions( -Wall -Wextra -Weffc++ -std=c++11 )
add_definitions( -Wall -Wextra -std=c++11 )
ADD_DEFINITIONS( -DBOOST_LOG_DYN_LINK )

#set( CMAKE_INCLUDE_CURRENT_DIR ON )
set( CMAKE_BUILD_TYPE Debug )

find_package( Boost COMPONENTS filesystem log log_setup date_time regex REQUIRED )

add_subdirectory( src )

SET_TARGET_PROPERTIES(${PROJECT_NAME} PROPERTIES COMPILE_FLAGS "-fPIC")

# INSTALL SHIT TO LOOK UP
#install( TARGETS ${PROJECT_NAME} DESTINATION . )