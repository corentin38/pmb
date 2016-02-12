CMAKE_MINIMUM_REQUIRED( VERSION 2.8 )
project( pmb-gui )

set( PMB_COMMON /home/corentin/.local/pmb )

#add_definitions( -Wall -Wextra -Werror -Weffc++ -std=c++11 )
#add_definitions( -Wall -Wextra -Weffc++ -std=c++11 )
add_definitions( -Wall -Wextra -std=c++11 -DBOOST_LOG_DYN_LINK )

set( CMAKE_INCLUDE_CURRENT_DIR ON )
set( CMAKE_AUTOMOC ON )
set( CMAKE_BUILD_TYPE Debug )

find_package( Qt5 REQUIRED Widgets )
find_package( Boost COMPONENTS thread system filesystem log log_setup date_time regex REQUIRED )
find_library( LIBPMB_COMMON libpmb-common.so PATHS ${PMB_COMMON} )

qt5_wrap_ui( QT_UI_FILES mainwindow.ui blogwizard.ui posteditor.ui )

include_directories(
  ${PMB_COMMON}/include
  SYSTEM ${Boost_INCLUDE_DIRS}
)

add_executable(
  ${PROJECT_NAME} 
  main.cpp
  blogwizard.cpp
  posteditor.cpp
  mainwindow.cpp
  ${QT_UI_FILES}
  ${QT_RCC_FILES}
)

target_link_libraries( ${PROJECT_NAME} 
  ${Boost_LIBRARIES}
  ${LIBPMB_COMMON}
)

qt5_use_modules( ${PROJECT_NAME} Widgets )

#install( TARGETS ${PROJECT_NAME} DESTINATION . )
