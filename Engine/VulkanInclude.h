#pragma once

#include <MemoryMacros.h>
#include <Types.h>

// Set defines for Vulkan loading
#ifdef PLATFORM_WINDOWS
#define VK_USE_PLATFORM_PLATFORM_WINDOWS_KHR
#elif defined PLATFORM_LINUX
#define VK_USE_PLATFORM_XLIB_KHR
#else
#error "Missing implementation for platform"
#endif

#ifdef PLATFORM_WINDOWS
#define VULKAN_DYNAMIC_LIBRARY "vulkan-1.dll"
#elif defined PLATFORM_LINUX
#define VULKAN_DYNAMIC_LIBRARY "Vulkan-1.so"
#else
#error "VULKAN_DYNAMIC_LIBRARY isn't defined for the platform"
#endif

#define EXTERN_DEFINE_VK_FUNCTION(FunctionName) extern PFN_##FunctionName FunctionName
#define LOAD_VK_FUNCTION(FunctionName) FunctionName = (PFN_##FunctionName)vkGetProcAddress(gVulkanInstance, #FunctionName)

// Define VK_NO_PROTOTYPES so we can use the same names for our functions as Vulkan does in the documentation
#define VK_NO_PROTOTYPES
#include <vulkan/vulkan.h>

// If we are including vulkan we might just as well include SDL
#include <SDL2/SDL.h>
// Everyone defs createwindow to be different things so we just undef it here
#undef CreateWindow

extern PFN_vkGetInstanceProcAddr vkGetProcAddress;
extern VkInstance gVulkanInstance;

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
EXTERN_DEFINE_VK_FUNCTION(vkCreateShaderModule);

#ifdef PLATFORM_WINDOWS
EXTERN_DEFINE_VK_FUNCTION(vkCreateWin32SurfaceKHR);
#elif defined PLATFORM_LINUX
EXTERN_DEFINE_VK_FUNCTION(vkCreateXlibSurfaceKHR);
#else
#error "Missing implemenatation for platform"
#endif
