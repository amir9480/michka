cmake_minimum_required(VERSION 3.0.0)
project(MichkaTests)

enable_testing()

set(TEST_SOURCES "")
add_subdirectory("Core")

add_executable(MichkaTests ${SOURCES} ${TEST_SOURCES})
target_link_libraries(MichkaTests gtest gtest_main)

add_test(MichkaTest MichkaTests)
