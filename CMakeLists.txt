cmake_minimum_required(VERSION 3.15)
project(shopping-list)

set(CMAKE_CXX_STANDARD 17)

set(CONFIG_LOCATION "/etc/shopping-list.d")
set(DEFAULT_CONFIGURATION_FILE ${CONFIG_LOCATION}/default.conf)

include(ExternalProject)
set(TEST_INSTALL_LOCATION ${PROJECT_SOURCE_DIR}/external-test)
set(EXTERNAL_INSTALL_LOCATION ${PROJECT_SOURCE_DIR}/external)
set(CONFIG_HEADER_LOCATION ${PROJECT_SOURCE_DIR}/config)
configure_file(${CONFIG_HEADER_LOCATION}/defaults.h.in ${CONFIG_HEADER_LOCATION}/defaults.h)

ExternalProject_Add(strong_types_ep
        GIT_REPOSITORY https://github.com/alexgunkel/strongtypes
        GIT_TAG v1.2
        GIT_PROGRESS true
        CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${EXTERNAL_INSTALL_LOCATION}
        )

ExternalProject_Add(googletest_ep
        GIT_REPOSITORY https://github.com/google/googletest
        GIT_TAG 78fdd6c00b8fa5dd67066fbb796affc87ba0e075
        GIT_PROGRESS true
        CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${TEST_INSTALL_LOCATION} -DCMAKE_INSTALL_LIBDIR=lib64 -DCMAKE_CXX_FLAGS="-w"
        )

add_subdirectory(src)

add_executable(shopping-list-server server.cpp)
target_link_libraries(shopping-list-server PUBLIC listHandler)

add_executable(user-ctl user_ctl.cpp)
target_link_libraries(user-ctl PRIVATE user_ctl)

install(
        DIRECTORY ${PROJECT_SOURCE_DIR}/data/
        DESTINATION ${CONFIG_LOCATION}
)

install(TARGETS shopping-list-server
        CONFIGURATIONS Release)

enable_testing()
add_subdirectory(test)
