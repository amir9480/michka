## ------------------------------------------------------------------------------- ##
##                                     Michka                                      ##
## ------------------------------------------------------------------------------- ##
##                                  MIT License                                    ##
##                                                                                 ##
## Copyright (c) 2020-2020 amir alizadeh.                                          ##
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
project(Michka VERSION 0.0.1)
set(CMAKE_CXX_STANDARD 17)

set(SOURCES "")

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/src")
add_subdirectory("src/Core")
add_subdirectory("src/Platform")

add_executable(Michka ${SOURCES} "${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp")
add_compile_definitions(_CRT_SECURE_NO_WARNINGS)
set_property(TARGET Michka PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
# target_link_libraries(Michka ${LIBS})

if(MICHKA_BUILD_TYPE STREQUAL "MinSizeRel")
    set(MICHKA_BUILD_TYPE "MinSizeRel")
elseif(MICHKA_BUILD_TYPE STREQUAL "RelWithDebInfo")
    set(MICHKA_BUILD_TYPE "RelWithDebInfo")
elseif(MICHKA_BUILD_TYPE STREQUAL "Release")
    set(MICHKA_BUILD_TYPE "Release")
else()
    set(MICHKA_BUILD_TYPE "Debug")
endif()

if(MICHKA_BUILD_TYPE STREQUAL "Debug")
    set(MICHKA_LIBRARY_POSTFIX "d")
else()
    set(MICHKA_LIBRARY_POSTFIX "")
endif()

option(PACKAGE_TESTS "Build the tests" ON)
if(PACKAGE_TESTS)
    # Build Google Test if library file does not exists
    if(EXISTS "${CMAKE_CURRENT_BINARY_DIR}/lib/${MICHKA_BUILD_TYPE}/gtest${MICHKA_LIBRARY_POSTFIX}.lib")
        include_directories("${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/googletest/googletest/include")
        link_directories("${CMAKE_CURRENT_BINARY_DIR}/lib/${MICHKA_BUILD_TYPE}")
        add_subdirectory("tests")
    else()
        set(gtest_force_shared_crt On)
        add_subdirectory("thirdparty/googletest")
        add_subdirectory("tests")
    endif()
endif()
