cmake_minimum_required(VERSION 3.8)

set(CMAKE_CXX_FLAGS "-Wall -std=c++11 -g")

add_subdirectory("Engine" "Engine")
add_subdirectory("Utils" "Utils")
add_subdirectory("thirdparty" "thirdparty")

link_directories($ENV{VK_SDK_PATH}/Lib)
link_directories($ENV{SDL2_SDK_PATH}/x86_64-w64-mingw32/lib)
include_directories(Utils)
include_directories(Engine)

add_executable(Cerberus "main.cpp")
target_link_libraries(Cerberus engine)
