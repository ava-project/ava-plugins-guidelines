# Minimum cmake version required
cmake_minimum_required(VERSION 3.2.0 FATAL_ERROR)

# Project name
set(PROJECT ava_api_protocol_communication)
project(${PROJECT} CXX)

# Build
IF (WIN32)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W3 /O2")
ELSE ()
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")
ENDIF (WIN32)

include_directories(tested/Hermes/include)

add_executable(test_server main.cpp)
