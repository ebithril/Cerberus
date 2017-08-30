cmake_minimum_required(VERSION 3.8)

set(CMAKE_CXX_FLAGS "-Wall -std=c++11 -g")
set(SOURCE_FILES FileOperations.cpp MemoryTracker.cpp UString.cpp)

add_library(utils STATIC ${SOURCE_FILES})