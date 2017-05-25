#pragma once

#include "EngineStructs.h"
#include "VulkanInclude.h"

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
	DEFINE_VKFUNCTIONPTR(vkGetPhysicalDeviceProperties);
	DEFINE_VKFUNCTIONPTR(vkGetPhysicalDeviceFeatures);
	DEFINE_VKFUNCTIONPTR(vkGetPhysicalDeviceQueueFamilyProperties);
	DEFINE_VKFUNCTIONPTR(vkCreateDevice);
	DEFINE_VKFUNCTIONPTR(vkGetDeviceQueue);
	DEFINE_VKFUNCTIONPTR(vkGetPhysicalDeviceSurfaceSupportKHR);
	DEFINE_VKFUNCTIONPTR(vkGetPhysicalDeviceSurfaceCapabilitiesKHR);
	DEFINE_VKFUNCTIONPTR(vkGetPhysicalDeviceSurfaceFormatsKHR);
	DEFINE_VKFUNCTIONPTR(vkGetPhysicalDeviceSurfacePresentModesKHR);
	DEFINE_VKFUNCTIONPTR(vkCreateSwapchainKHR);
	DEFINE_VKFUNCTIONPTR(vkGetSwapchainImagesKHR);
	DEFINE_VKFUNCTIONPTR(vkCreateImageView);
	DEFINE_VKFUNCTIONPTR(vkCreateWin32SurfaceKHR);

private:
	VulkanInstance* myInstance;
};
