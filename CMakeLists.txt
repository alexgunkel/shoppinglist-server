cmake_minimum_required(VERSION 3.15)
project(list)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(src)

add_executable(list main.cpp)
target_link_libraries(list PRIVATE listHandler)
