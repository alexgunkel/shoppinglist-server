
include_directories(${PROJECT_SOURCE_DIR}/src)
include_directories(${TEST_INSTALL_LOCATION}/include)
link_directories(${TEST_INSTALL_LOCATION}/lib64)

set(TEST_FIXTURE_LOCATION "${CMAKE_CURRENT_SOURCE_DIR}/fixtures")
configure_file(test_config.h.in ${TEST_INSTALL_LOCATION}/include/test_config.h)

find_package(cpprestsdk REQUIRED)

file(GLOB model-test-sources "unit/model/*")
add_executable(model-test unit/unit_test_main.cpp ${model-test-sources})
target_link_libraries(model-test PRIVATE model gtest pthread)
add_test(model-test model-test)
add_dependencies(model-test googletest_ep)

file(GLOB config-test-sources "unit/config/*")
add_executable(config-test unit/unit_test_main.cpp ${config-test-sources})
target_link_libraries(config-test PRIVATE config gtest pthread)
add_dependencies(config-test googletest_ep)
add_test(config-test config-test)

file(GLOB api-test-sources "unit/api/*")
add_executable(api-test unit/unit_test_main.cpp ${api-test-sources})
target_link_libraries(api-test PRIVATE api gtest gmock pthread)
add_dependencies(api-test googletest_ep)
add_test(api-test api-test)

file(GLOB serde-test-sources "unit/serde/*")
add_executable(serde-test unit/unit_test_main.cpp ${serde-test-sources})
target_link_libraries(serde-test PRIVATE serde gtest gmock pthread)
add_dependencies(serde-test googletest_ep)
add_test(serde-test serde-test)
