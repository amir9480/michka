cmake_minimum_required(VERSION 3.0.0)
project(MishkaTests)

file(GLOB testSources "${CMAKE_CURRENT_SOURCE_DIR}/Core/*.cpp" PARENT_SCOPE)

add_executable(MishkaTests ${SOURCES} ${testSources})
target_link_libraries(MishkaTests gtest gtest_main)

add_test(MishkaTest MishkaTests)
