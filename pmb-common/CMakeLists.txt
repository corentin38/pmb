CMAKE_MINIMUM_REQUIRED( VERSION 2.8 )
project( pmb-common )

# You can set the CMAKE_INSTALL_PREFIX by passing : -DCMAKE_INSTALL_PREFIX=/home/corentin/.local
message("Install prefix provided: " ${CMAKE_INSTALL_PREFIX})

## MAKE SURE THIS POINTS TO PROPER RESOURCE FILES ################
set( RESOURCES ${CMAKE_INSTALL_PREFIX}/share/pmb )

set( TEMPLATE_RESOURCE ${RESOURCES}/page.tpl )
set( CONTENT_SAMPLE_RESOURCE ${RESOURCES}/content_sample.xml )
set( CONTENT_EMPTY_RESOURCE ${RESOURCES}/content_empty.xml )
set( BOOTSTRAP_RESOURCE ${RESOURCES}/dist )
set( CSS_RESOURCE ${RESOURCES}/blog.css )
set( SYNC_SCRIPT ${RESOURCES}/sync.sh )
set( SUBMIT_SCRIPT ${RESOURCES}/submit.sh )

configure_file(
  ${CMAKE_SOURCE_DIR}/include/gen/blog_constants.hpp.in
  ${CMAKE_SOURCE_DIR}/include/gen/blog_constants.hpp
)

configure_file(
  ${CMAKE_SOURCE_DIR}/include/gen/script_constants.hpp.in
  ${CMAKE_SOURCE_DIR}/include/gen/script_constants.hpp
)
##################################################################

#add_definitions( -Wall -Wextra -Werror -Weffc++ -std=c++11 )
#add_definitions( -Wall -Wextra -Weffc++ -std=c++11 )
add_definitions( -Wall -Wextra -std=c++11 -DBOOST_LOG_DYN_LINK )

set( CMAKE_BUILD_TYPE Debug )

find_package( Boost COMPONENTS filesystem log log_setup date_time regex REQUIRED )

include_directories(
  ${CMAKE_SOURCE_DIR}/lib/flate
  SYSTEM ${Boost_INCLUDE_DIRS}
  ${CMAKE_SOURCE_DIR}/include
)

add_subdirectory( src )

# pmb-common library
add_library( ${PROJECT_NAME} SHARED
  src/factory_blog.cpp
  src/blog_local.cpp
  src/persistor_blog.cpp
  src/controller_blog.cpp
  src/persistable_blog.cpp
  src/generator.cpp
  src/configuration_blog.cpp
  src/ssh_moulinator.cpp
)

SET_TARGET_PROPERTIES(${PROJECT_NAME} PROPERTIES COMPILE_FLAGS "-fPIC")

# YOU NEED TO BUILD LIBFLATE IN pmb-common/libs/flate BEFORE BUILD
#   $ cd pmb-common/libs/flate
#   $ make
find_library( FLATE libflate.a PATHS ${CMAKE_SOURCE_DIR}/lib/flate )
target_link_libraries( ${PROJECT_NAME}
  utils
  cppmarkdown
  ${Boost_LIBRARIES}
  ${FLATE}
)


# INSTALL

# # RESOURCES
install(FILES
  resources/page.tpl
  resources/content_sample.xml
  resources/content_empty.xml
  resources/blog.css

  DESTINATION
  share/pmb
)
install(PROGRAMS
  resources/sync.sh
  resources/submit.sh

  DESTINATION
  share/pmb
)
install(DIRECTORY resources/dist DESTINATION share/pmb)

# # INCLUDES
install(DIRECTORY include DESTINATION pmb)

# # LIBRARY
install(TARGETS ${PROJECT_NAME} LIBRARY DESTINATION pmb)
