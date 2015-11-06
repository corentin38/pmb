CMAKE_MINIMUM_REQUIRED( VERSION 2.8 )

project( pmb )

set( CMAKE_INCLUDE_CURRENT_DIR ON )
set( CMAKE_AUTOMOC ON )
set( CMAKE_BUILD_TYPE Debug )

add_definitions( -Wall -Wextra )

find_package( Qt5 REQUIRED Widgets )

qt5_wrap_ui( QT_UI_FILES resources/interface/mainwindow.ui )

add_subdirectory( lib )

add_executable(
    ${PROJECT_NAME} 
    MainWindow/main.cpp
    MainWindow/mainwindow.cpp
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
