#pragma once

#include "Include/vulkan/vulkan.h"

#define LOAD_VULKAN_FUNCTION(vkInstance, FunctionName) fp##FunctionName = (PFN_##FunctionName)VulkanLoader::vkGetProcAddress(vkInstance, #FunctionName)
#define DEFINE_VKFUNCTIONPTR(FunctionName) PFN_##FunctionName fp##FunctionName