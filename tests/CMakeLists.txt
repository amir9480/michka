## ------------------------------------------------------------------------------- ##
##                                     Michka                                      ##
## ------------------------------------------------------------------------------- ##
##                                  MIT License                                    ##
##                                                                                 ##
## Copyright (c) 2020-2021 amir alizadeh.                                          ##
##                                                                                 ##
## Permission is hereby granted, free of charge, to any person obtaining a copy    ##
## of this software and associated documentation files (the "Software"), to deal   ##
## in the Software without restriction, including without limitation the rights    ##
## to use, copy, modify, merge, publish, distribute, sublicense, and/or sell       ##
## copies of the Software, and to permit persons to whom the Software is           ##
## furnished to do so, subject to the following conditions:                        ##
##                                                                                 ##
## The above copyright notice and this permission notice shall be included in all  ##
## copies or substantial portions of the Software.                                 ##
##                                                                                 ##
## THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR      ##
## IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,        ##
## FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE     ##
## AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER          ##
## LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,   ##
## OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE   ##
## SOFTWARE.                                                                       ##
## ------------------------------------------------------------------------------- ##

cmake_minimum_required(VERSION 3.0.0)
project(MichkaTests)

set(TEST_SOURCES "")

include_directories("${CMAKE_CURRENT_SOURCE_DIR}")

add_subdirectory("Classes")
add_subdirectory("Core")
add_subdirectory("Graphics")
add_subdirectory("Platform")

set(TEST_SOURCES ${SOURCES} "${CMAKE_CURRENT_SOURCE_DIR}/MichkaTests.cpp")

add_compile_definitions(MICHKA_TESTS_PATH="${CMAKE_CURRENT_SOURCE_DIR}")
add_executable(MichkaTests ${MAIN_SOURCES} ${TEST_SOURCES})
set_property(TARGET MichkaTests PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
set_property(TARGET MichkaTests PROPERTY CXX_STANDARD 17)
target_link_libraries(MichkaTests ${LIBS})

if(MICHKA_BUILD_TYPE STREQUAL "Debug")
    target_link_libraries(MichkaTests gtestd gtest_maind)
else()
    target_link_libraries(MichkaTests gtest gtest_main)
endif()
