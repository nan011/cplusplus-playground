# CMake minimum required version
cmake_minimum_required(VERSION 3.10)

# Project name and version
project(run VERSION 1.0)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(run main.cpp)