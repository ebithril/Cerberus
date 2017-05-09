#include "VulkanLoader.h"

#include "VulkanInstance.h"

#include <stdio.h>

PFN_vkGetInstanceProcAddr VulkanLoader::vkGetProcAddress = NULL;

void VulkanLoader::Init(VulkanInstance* Instance)
{
	myInstance = Instance;
}

void VulkanLoader::LoadFunctions()
{
	if (!myInstance)
	{
		return;
	}

	LOAD_VULKAN_FUNCTION(myInstance->VulkanInstance, vkEnumeratePhysicalDevices);
	LOAD_VULKAN_FUNCTION(myInstance->VulkanInstance, vkGetPhysicalDeviceProperties);
	LOAD_VULKAN_FUNCTION(myInstance->VulkanInstance, vkGetPhysicalDeviceFeatures);
	LOAD_VULKAN_FUNCTION(myInstance->VulkanInstance, vkGetPhysicalDeviceQueueFamilyProperties);
}