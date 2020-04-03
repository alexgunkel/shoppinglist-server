
include_directories(${PROJECT_SOURCE_DIR}/src)
include_directories(${TEST_INSTALL_LOCATION}/include)
link_directories(${TEST_INSTALL_LOCATION}/lib64)

find_package(cpprestsdk REQUIRED)

file(GLOB model-test-sources "unit/model/*")
add_executable(model-test unit_test_main.cpp ${model-test-sources})
target_link_libraries(model-test PRIVATE model gtest pthread)
add_test(model-test model-test)

file(GLOB api-test-sources "unit/api/*")
add_executable(api-test unit_test_main.cpp ${api-test-sources})
target_link_libraries(api-test PRIVATE api gtest gmock pthread)
add_test(api-test api-test)

file(GLOB serde-test-sources "unit/serde/*")
add_executable(serde-test unit_test_main.cpp ${serde-test-sources})
target_link_libraries(serde-test PRIVATE serde gtest gmock pthread)
add_test(serde-test serde-test)

file(GLOB unit-test-sources "unit/*_test.cpp")
file(GLOB mocks "mocks/*.h")

add_executable(server-tests "")
target_sources(server-tests PRIVATE unit_test_main.cpp ${unit-test-sources} ${mocks})
target_link_libraries(server-tests PUBLIC listHandler gtest gmock pthread)
add_dependencies(server-tests googletest_ep listHandler)
add_test(server-test server-tests)
