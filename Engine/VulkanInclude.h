#pragma once

// Set defines for Vulkan loading
#define VK_USE_PLATFORM_WIN32_KHR
#define VK_NO_PROTOTYPES

#include <vulkan/vulkan.h>
#undef CreateWindow

vkGetProcAddress = (PFN_vkGetInstanceProcAddr)SDL_LoadFunction(SDL_LoadObject("vulkan-1.dll", "vkGetInstanceProcAddr"));

extern VkInstance gVulkanInstance;
extern PFN_vkGetInstanceProcAddr vkGetProcAddress;

#define DEFINE_VK_FUNCTION(FunctionName) PFN_##FunctionName FunctionName
#define LOAD_VK_FUNCTION(FunctionName) FunctionName = (PFN_##FunctionName)vkGetProcAddress(gVulkanInstance, #FunctionName)

DEFINE_VK_FUNCTION(vkCreateInstance);
DEFINE_VK_FUNCTION(vkEnumerateInstanceLayerProperties);
DEFINE_VK_FUNCTION(vkEnumerateInstanceExtensionProperties);

DEFINE_VK_FUNCTION(vkEnumeratePhysicalDevices);
DEFINE_VK_FUNCTION(vkGetPhysicalDeviceProperties);
DEFINE_VK_FUNCTION(vkGetPhysicalDeviceFeatures);
DEFINE_VK_FUNCTION(vkGetPhysicalDeviceQueueFamilyProperties);
DEFINE_VK_FUNCTION(vkCreateDevice);
DEFINE_VK_FUNCTION(vkGetDeviceQueue);
DEFINE_VK_FUNCTION(vkGetPhysicalDeviceSurfaceSupportKHR);
DEFINE_VK_FUNCTION(vkGetPhysicalDeviceSurfaceCapabilitiesKHR);
DEFINE_VK_FUNCTION(vkGetPhysicalDeviceSurfaceFormatsKHR);
DEFINE_VK_FUNCTION(vkGetPhysicalDeviceSurfacePresentModesKHR);
DEFINE_VK_FUNCTION(vkCreateSwapchainKHR);
DEFINE_VK_FUNCTION(vkGetSwapchainImagesKHR);
DEFINE_VK_FUNCTION(vkCreateImageView);
DEFINE_VK_FUNCTION(vkCreateWin32SurfaceKHR);
DEFINE_VK_FUNCTION(vkCreateShaderModule);

