
find_package(cpprestsdk REQUIRED)

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
target_include_directories(config PUBLIC ${EXTERNAL_INSTALL_LOCATION}/include)

file(GLOB api_sources api/*)
add_library(api STATIC ${api_sources})
target_link_libraries(api PUBLIC model serde cpprestsdk::cpprest)
target_compile_options(api PRIVATE -Werror -Wall -Wextra)
add_dependencies(api serde model)

file(GLOB list_sources *.cpp)
file(GLOB list_headers *.h)
add_library(listHandler STATIC ${list_sources} ${list_headers})
target_include_directories(listHandler PUBLIC ${EXTERNAL_INSTALL_LOCATION}/include)
target_link_libraries(listHandler PUBLIC api config)
target_compile_options(listHandler PRIVATE -Werror -Wall -Wextra)
add_dependencies(listHandler strong_types_ep api)
