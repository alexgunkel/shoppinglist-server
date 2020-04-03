

include_directories(${PROJECT_SOURCE_DIR}/src)
include_directories(${TEST_INSTALL_LOCATION}/include)
link_directories(${TEST_INSTALL_LOCATION}/lib64)

file(GLOB unit-test-sources "unit/*_test.cpp")
file(GLOB mocks "mocks/*.h")

find_package(cpprestsdk REQUIRED)

add_executable(unit-tests "")
target_sources(unit-tests PRIVATE unit_test_main.cpp ${unit-test-sources} ${mocks})
target_link_libraries(unit-tests PRIVATE listHandler gtest gmock pthread)
add_dependencies(unit-tests googletest_ep listHandler)
