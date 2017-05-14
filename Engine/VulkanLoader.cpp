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
	LOAD_VULKAN_FUNCTION(myInstance->VulkanInstance, vkCreateDevice);
	LOAD_VULKAN_FUNCTION(myInstance->VulkanInstance, vkGetDeviceQueue);
	LOAD_VULKAN_FUNCTION(myInstance->VulkanInstance, vkGetPhysicalDeviceSurfaceSupportKHR);
	LOAD_VULKAN_FUNCTION(myInstance->VulkanInstance, vkGetPhysicalDeviceSurfaceCapabilitiesKHR);
	LOAD_VULKAN_FUNCTION(myInstance->VulkanInstance, vkGetPhysicalDeviceSurfaceFormatsKHR);
	LOAD_VULKAN_FUNCTION(myInstance->VulkanInstance, vkGetPhysicalDeviceSurfacePresentModesKHR);
	LOAD_VULKAN_FUNCTION(myInstance->VulkanInstance, vkCreateSwapchainKHR);
	LOAD_VULKAN_FUNCTION(myInstance->VulkanInstance, vkGetSwapchainImagesKHR);
}
