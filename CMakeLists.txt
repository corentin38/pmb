CMAKE_MINIMUM_REQUIRED( VERSION 2.8 )

project( pmb )

## MAKE SURE THIS POINTS TO PROPER RESOURCE FILES ################
set( XSL_RESOURCE ${CMAKE_SOURCE_DIR}/resources/dom/my.xsl )
set( CONFIG_RESOURCE ${CMAKE_SOURCE_DIR}/resources/dom/config.xml )
set( CONTENT_SAMPLE_RESOURCE ${CMAKE_SOURCE_DIR}/resources/dom/content_sample.xml )
set( CONTENT_EMPTY_RESOURCE ${CMAKE_SOURCE_DIR}/resources/dom/content_empty.xml )
set( BOOTSTRAP_RESOURCE ${CMAKE_SOURCE_DIR}/resources/dom/dist )
set( CSS_RESOURCE ${CMAKE_SOURCE_DIR}/resources/dom/blog.css )
##################################################################

set( CMAKE_INCLUDE_CURRENT_DIR ON )
set( CMAKE_AUTOMOC ON )
set( CMAKE_BUILD_TYPE Debug )

configure_file( 
  ${CMAKE_SOURCE_DIR}/lib/gen/blog_constants.hpp.in 
  ${CMAKE_SOURCE_DIR}/lib/gen/blog_constants.hpp 
)

#add_definitions( -Wall -Wextra -Werror -Weffc++ -std=c++11 )
#add_definitions( -Wall -Wextra -Weffc++ -std=c++11 )
add_definitions( -Wall -Wextra -std=c++11 )
ADD_DEFINITIONS( -DBOOST_LOG_DYN_LINK )

find_package( Qt5 REQUIRED Widgets )
find_package( Threads REQUIRED )
find_package( Boost COMPONENTS system filesystem log log_setup thread date_time REQUIRED )

qt5_wrap_ui( QT_UI_FILES interface/mainwindow.ui interface/blogwizard.ui interface/posteditor.ui )

add_subdirectory( libc )
add_subdirectory( lib )

add_executable(
    ${PROJECT_NAME} 
    main.cpp
    interface/blogwizard.cpp
    interface/posteditor.cpp
    interface/mainwindow.cpp
    ${QT_UI_FILES}
    ${QT_RCC_FILES}
)

include_directories(
    ${Boost_INCLUDE_DIR}
    ${LIBXML2_INCLUDE_DIR}
    ${LIBXSLT_INCLUDE_DIR}
    ${CMAKE_SOURCE_DIR}/lib/include
)

target_link_libraries( ${PROJECT_NAME} blog )

qt5_use_modules( ${PROJECT_NAME} Widgets )

install( TARGETS ${PROJECT_NAME} DESTINATION . )
