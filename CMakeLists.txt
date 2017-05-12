cmake_minimum_required(VERSION 3.6)
project(cpptest)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp AbsoluteURLParser.cpp AbsoluteURLParser.h)
add_executable(cpptest ${SOURCE_FILES})