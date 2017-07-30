cmake_minimum_required(VERSION 3.8)

set(CMAKE_CXX_FLAGS "-Wall -std?c++11 -g")
set(SOURCE_FILES)

add_library(thirdparty STATIC ${SOURCE_FILES})
set_target_properties(thirdparty PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(thirdparty PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
