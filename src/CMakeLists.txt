
find_package(cpprestsdk REQUIRED)

file(GLOB list_sources *.cpp)
file(GLOB list_headers *.h)
add_library(listHandler STATIC ${list_sources} ${list_headers})
target_include_directories(listHandler PUBLIC ${EXTERNAL_INSTALL_LOCATION}/include)
target_link_libraries(listHandler PUBLIC cpprestsdk::cpprest)
target_compile_options(listHandler PRIVATE -Werror -Wall -Wextra)
add_dependencies(listHandler strong_types_ep)
