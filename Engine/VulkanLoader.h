#pragma once

#include "EngineStructs.h"
#include "Include/vulkan/vulkan.h"

#define LOAD_VULKAN_FUNCTION(vkInstance, FunctionName) fp##FunctionName = (PFN_##FunctionName)VulkanLoader::vkGetProcAddress((vkInstance), #FunctionName)
#define DEFINE_VKFUNCTIONPTR(FunctionName) PFN_##FunctionName fp##FunctionName

class VulkanInstance;

class VulkanLoader
{
public:
	void Init(VulkanInstance* Instance);
	void LoadFunctions();

	static PFN_vkGetInstanceProcAddr vkGetProcAddress;

	DEFINE_VKFUNCTIONPTR(vkEnumeratePhysicalDevices);

private:
	VulkanInstance* myInstance;
};