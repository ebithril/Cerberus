#pragma once

// Set defines for Vulkan loading
#define VK_USE_PLATFORM_WIN32_KHR
#define VK_NO_PROTOTYPES

#include <vulkan/vulkan.h>
#include <SDL2/SDL.h>
#undef CreateWindow

extern PFN_vkGetInstanceProcAddr vkGetProcAddress;
extern VkInstance gVulkanInstance;

#define EXTERN_DEFINE_VK_FUNCTION(FunctionName) extern PFN_##FunctionName FunctionName
#define LOAD_VK_FUNCTION(FunctionName) FunctionName = (PFN_##FunctionName)vkGetProcAddress(gVulkanInstance, #FunctionName)

// Functions that doesn't need a VulkanInstance to load
EXTERN_DEFINE_VK_FUNCTION(vkCreateInstance);
EXTERN_DEFINE_VK_FUNCTION(vkEnumerateInstanceLayerProperties);
EXTERN_DEFINE_VK_FUNCTION(vkEnumerateInstanceExtensionProperties);

// Functions that need VulkanInstance or Device to be inited
EXTERN_DEFINE_VK_FUNCTION(vkEnumeratePhysicalDevices);
EXTERN_DEFINE_VK_FUNCTION(vkGetPhysicalDeviceProperties);
EXTERN_DEFINE_VK_FUNCTION(vkGetPhysicalDeviceFeatures);
EXTERN_DEFINE_VK_FUNCTION(vkGetPhysicalDeviceQueueFamilyProperties);
EXTERN_DEFINE_VK_FUNCTION(vkCreateDevice);
EXTERN_DEFINE_VK_FUNCTION(vkGetDeviceQueue);
EXTERN_DEFINE_VK_FUNCTION(vkGetPhysicalDeviceSurfaceSupportKHR);
EXTERN_DEFINE_VK_FUNCTION(vkGetPhysicalDeviceSurfaceCapabilitiesKHR);
EXTERN_DEFINE_VK_FUNCTION(vkGetPhysicalDeviceSurfaceFormatsKHR);
EXTERN_DEFINE_VK_FUNCTION(vkGetPhysicalDeviceSurfacePresentModesKHR);
EXTERN_DEFINE_VK_FUNCTION(vkCreateSwapchainKHR);
EXTERN_DEFINE_VK_FUNCTION(vkGetSwapchainImagesKHR);
EXTERN_DEFINE_VK_FUNCTION(vkCreateImageView);
EXTERN_DEFINE_VK_FUNCTION(vkCreateWin32SurfaceKHR);
EXTERN_DEFINE_VK_FUNCTION(vkCreateShaderModule);

