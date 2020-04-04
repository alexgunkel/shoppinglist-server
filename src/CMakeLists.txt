
find_package(cpprestsdk REQUIRED)
find_library(cryptopp REQUIRED)

file(GLOB model_sources model/*)
add_library(model STATIC ${model_sources})
target_compile_options(model PRIVATE -Werror -Wall -Wextra)
target_include_directories(model PUBLIC ${EXTERNAL_INSTALL_LOCATION}/include)
add_dependencies(model strong_types_ep)

file(GLOB serde_sources serde/*)
add_library(serde STATIC ${serde_sources})
target_link_libraries(serde PUBLIC model cpprestsdk::cpprest)
target_compile_options(serde PRIVATE -Werror -Wall -Wextra)
add_dependencies(serde model)

file(GLOB config_sources config/*)
add_library(config STATIC ${config_sources})
target_compile_options(config PRIVATE -Werror -Wall -Wextra)
target_include_directories(config PUBLIC ${EXTERNAL_INSTALL_LOCATION}/include ${CONFIG_HEADER_LOCATION})
add_dependencies(config strong_types_ep)

file(GLOB api_sources api/*)
add_library(api STATIC ${api_sources})
target_link_libraries(api PUBLIC model serde cpprestsdk::cpprest cryptopp)
target_compile_options(api PRIVATE -Werror -Wall -Wextra)
add_dependencies(api serde model)

add_library(listHandler STATIC ListServer.h ListServer.cpp)
target_include_directories(listHandler PUBLIC ${EXTERNAL_INSTALL_LOCATION}/include)
target_link_libraries(listHandler PUBLIC api config)
target_compile_options(listHandler PRIVATE -Werror -Wall -Wextra)
add_dependencies(listHandler strong_types_ep api)

add_library(user_ctl STATIC user_ctl.cpp user_ctl.h exceptions.h)
target_include_directories(user_ctl PUBLIC ${EXTERNAL_INSTALL_LOCATION}/include)
target_link_libraries(user_ctl PUBLIC model api config)
add_dependencies(user_ctl model)
