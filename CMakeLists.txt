cmake_minimum_required(VERSION 3.15)
project(shopping-list)

set(CMAKE_CXX_STANDARD 17)

include(ExternalProject)
set(TEST_INSTALL_LOCATION ${PROJECT_SOURCE_DIR}/external-test)
set(EXTERNAL_INSTALL_LOCATION ${PROJECT_SOURCE_DIR}/external)

ExternalProject_Add(strong_types_ep
        GIT_REPOSITORY https://github.com/alexgunkel/strongtypes
        GIT_TAG v1.1
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

add_executable(shopping-list main.cpp)
target_link_libraries(shopping-list PUBLIC listHandler)

install(TARGETS shopping-list
        CONFIGURATIONS Release)

enable_testing()
add_subdirectory(test)
