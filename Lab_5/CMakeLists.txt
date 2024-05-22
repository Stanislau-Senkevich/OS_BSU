cmake_minimum_required(VERSION 3.10)
project(Lab_5)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(include)
add_executable(Lab_5 src/client.cpp src/server.cpp
        tests/tests.cpp
        src/employee.cpp)

add_subdirectory(googletest)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

enable_testing()
add_subdirectory(tests)