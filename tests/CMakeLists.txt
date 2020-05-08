cmake_minimum_required(VERSION 3.0.0)
project(MichkaTests)

enable_testing()

file(GLOB testSources "${CMAKE_CURRENT_SOURCE_DIR}/Core/*.cpp" PARENT_SCOPE)

add_executable(MichkaTests ${SOURCES} ${testSources})
target_link_libraries(MichkaTests gtest gtest_main)

add_test(MichkaTest MichkaTests)
