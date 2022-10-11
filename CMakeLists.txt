cmake_minimum_required(VERSION 3.20)
project(virus)

set(CMAKE_CXX_STANDARD 20)

add_executable(virus main.cpp FolderTerrorist.cpp FolderTerrorist.h)
set(GCC_COVERAGE_COMPILE_FLAGS "-pthread")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}" )

SET(CMAKE_CXX_FLAGS -pthread)