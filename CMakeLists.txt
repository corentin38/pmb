CMAKE_MINIMUM_REQUIRED( VERSION 2.8 )

project( pmb )

set( CMAKE_INCLUDE_CURRENT_DIR ON )
set( CMAKE_AUTOMOC ON )

find_package( Qt5 REQUIRED Widgets )
#find_package( Boost REQUIRED regex filesystem system )
#include( enable_rc )

#qt5_add_resources( QT_RCC_FILES resources/resources.qrc )
qt5_wrap_ui( QT_UI_FILES resources/interface/mainwindow.ui )

#add_definitions( -DQT_NO_OPENGL )

add_subdirectory( post )
add_subdirectory( blog )

add_executable(
    ${PROJECT_NAME} 
    MainWindow/main.cpp
    MainWindow/mainwindow.cpp
    ${QT_UI_FILES}
    ${QT_RCC_FILES}
#    "win32/resources.rc"
)

#include_directories(
#    include
#    ${CMAKE_SOURCE_DIR}/utils/src/include
#    ${CMAKE_SOURCE_DIR}/splitator/src
#    ${Boost_INCLUDE_DIR}
#)

target_link_libraries( ${PROJECT_NAME} post blog )
#add_dependencies( ${PROJECT_NAME} splitator_cmd )
qt5_use_modules( ${PROJECT_NAME} Widgets )

install( TARGETS ${PROJECT_NAME} DESTINATION . )
