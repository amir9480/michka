cmake_minimum_required(VERSION 3.0.0)
project(Michka VERSION 0.0.1)
set(CMAKE_CXX_STANDARD 17)

set(SOURCES "")

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/src")
add_subdirectory("src/Core")
add_subdirectory("src/Platform")

add_executable(Michka ${SOURCES} "${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp")
add_compile_definitions(_CRT_SECURE_NO_WARNINGS)

# target_link_libraries(Michka ${LIBS})

option(PACKAGE_TESTS "Build the tests" ON)
if(PACKAGE_TESTS)
    set(gtest_force_shared_crt On)
    add_subdirectory("thirdparty/googletest")
    include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
    add_subdirectory("tests")
endif()
