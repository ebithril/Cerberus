cmake_minimum_required(VERSION 3.8)

set(CMAKE_CXX_FLAGS "-Wall -std=c++11 -g")
set(SOURCE_FILES Engine.cpp VulkanEngine.cpp SDLWindow.cpp Window.cpp VulkanDevice.cpp VulkanLoader.cpp VulkanInstance.cpp VulkanShader.cpp VulkanVertexShader.cpp)

link_directories($ENV{VK_SDK_PATH}/Lib)
link_directories($ENV{SDL2_SDK_PATH}/x86_64-w64-mingw32/lib)
include_directories($ENV{VK_SDK_PATH}/Include)
include_directories($ENV{SDL2_SDK_PATH}/x86_64-w64-mingw32/include)
include_directories(../Utils)

add_library(engine STATIC ${SOURCE_FILES})
set_target_properties(engine PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(engine PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)

target_link_libraries(engine utils)
target_link_libraries(engine vulkan-1)
target_link_libraries(engine shaderc_combined)
target_link_libraries(engine SDL2)
target_link_libraries(engine SDL2main)