cmake_minimum_required(VERSION 3.10)
project(Lab_4)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(include)
add_executable(Lab_4 src/receiver.cpp src/sender.cpp
        tests/tests.cpp
        include/sendMsg.h
        src/sendMsg.cpp)

add_subdirectory(googletest)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

enable_testing()
add_subdirectory(tests)