cmake_minimum_required(VERSION 3.0.0)
project(MishkaTests)

file(GLOB testSources "Core/*.cpp")

add_executable(MishkaTests ${testSources})
target_link_libraries(MishkaTests gtest gtest_main)

add_test(MishkaTest MishkaTests)