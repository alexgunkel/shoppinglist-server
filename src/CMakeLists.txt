
include(ExternalProject)

set(EXTERNAL_INSTALL_DIR ${PROJECT_SOURCE_DIR}/external)

ExternalProject_add(uSockets_ep
        GIT_REPOSITORY https://github.com/uNetworking/uSockets
        GIT_PROGRESS true
        CONFIGURE_COMMAND ""
        SOURCE_DIR "${EXTERNAL_INSTALL_DIR}/usockets"
        INSTALL_COMMAND ""
        BUILD_IN_SOURCE true
        )
file(GLOB usocketlibs ${EXTERNAL_INSTALL_DIR}/usockets/*.o)
file(GLOB usocketstatic ${EXTERNAL_INSTALL_DIR}/usockets/*.a)

ExternalProject_Add(mWs_ep
        GIT_REPOSITORY https://github.com/uNetworking/uWebSockets
        GIT_PROGRESS true
        CONFIGURE_COMMAND ""
        BUILD_COMMAND ""
        BUILD_IN_SOURCE true
        INSTALL_COMMAND cp -r ./src ${EXTERNAL_INSTALL_DIR}/include/
        )
add_dependencies(mWs_ep uSockets_ep)

find_package(ZLIB)

add_library(listHandler STATIC List.h List.cpp)
target_include_directories(listHandler PRIVATE ${EXTERNAL_INSTALL_DIR}/include)
target_include_directories(listHandler PRIVATE ${EXTERNAL_INSTALL_DIR}/usockets/src)
target_link_libraries(listHandler PUBLIC ZLIB::ZLIB ${usocketlibs} ${usocketstatic})
add_dependencies(listHandler mWs_ep)
