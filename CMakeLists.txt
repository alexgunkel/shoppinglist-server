cmake_minimum_required(VERSION 3.15)
project(list)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(src)
add_subdirectory(test)

add_executable(shopping-list main.cpp)
target_link_libraries(shopping-list PRIVATE listHandler)

install(TARGETS shopping-list
        CONFIGURATIONS Release)
