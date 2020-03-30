
find_package(cpprestsdk REQUIRED)

add_library(listHandler STATIC List.h List.cpp ListServer.h ListServer.cpp RequestHandler.h RequestHandler.cpp)
target_link_libraries(listHandler PUBLIC cpprestsdk::cpprest)
