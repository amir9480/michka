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
project(Michka VERSION 0.0.1)


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

set(SOURCES "")
set(GENERATOR_COMMAND python scripts/generator.py ./src=./build/Generated/MichkaGenerated ./tests=./build/Generated/MichkaGenerated/tests)

if(NOT EXISTS ./build/Generated/MichkaGenerated/CMakeList.txt)
    execute_process(
        COMMAND ${GENERATOR_COMMAND}
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    )
endif()

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/src")
include_directories("${CMAKE_CURRENT_BINARY_DIR}/Generated")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/glad/include")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/opengl")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/stb")
add_subdirectory("src/Core")
add_subdirectory("src/Graphics")
add_subdirectory("src/Platform")
add_subdirectory("${CMAKE_CURRENT_BINARY_DIR}/Generated/MichkaGenerated")

set(
    MAIN_SOURCES
    ${SOURCES}
    ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/glad/src/glad.c
)

add_compile_definitions(_CRT_SECURE_NO_WARNINGS)
add_compile_definitions(MICHKA_SRC_PATH="${CMAKE_CURRENT_SOURCE_DIR}")
add_executable(Michka ${MAIN_SOURCES} "${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp")
set_property(TARGET Michka PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
set(
    LIBS
    opengl32.lib
)
target_link_libraries(Michka ${LIBS})
set_property(TARGET Michka PROPERTY CXX_STANDARD 17)

add_custom_command(
    TARGET Michka
    PRE_BUILD
    COMMAND python scripts/build.py ${MICHKA_BUILD_TYPE}
    COMMAND ${GENERATOR_COMMAND}
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    VERBATIM
)

option(PACKAGE_TESTS "Build the tests" ON)
if(PACKAGE_TESTS)
    include_directories("${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/googletest/googletest/include")
    link_directories("${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/build/googletest/lib/${MICHKA_BUILD_TYPE}")

    set(SOURCES "")
    add_subdirectory("${CMAKE_CURRENT_BINARY_DIR}/Generated/MichkaGenerated/tests")
    add_subdirectory("tests" ${CMAKE_CURRENT_BINARY_DIR}/tests)
endif()
