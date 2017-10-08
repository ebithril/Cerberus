#include "VulkanEngine.h"

#include <SDL2/SDL.h>
#include <Logging.h>

#include "Window.h"
#include "VulkanInclude.h"
#include "VulkanInstance.h"
#include "VulkanDevice.h"

void VulkanEngine::InitVulkan(const EngineStartupOptions& StartUpOptions)
{
	vkGetProcAddress = (PFN_vkGetInstanceProcAddr)SDL_LoadFunction(
		SDL_LoadObject("vulkan-1.dll"), 
		"vkGetInstanceProcAddr");

	myInstance = new VulkanInstance();
	if (ensure(myInstance))
	{
		myInstance->Create();
	}

	if (!ensure(LoadFunctions()))
	{
		return;
	}

	myWindow = new Window();
	if (ensure(myWindow))
	{
		myWindow->CreateWindow(
			StartUpOptions.myWindowMode, 
			StartUpOptions.myWindowWidth, 
			StartUpOptions.myWindowHeight, 
			myInstance);
	}

	myDevice = new VulkanDevice();
	if (myDevice)
	{
		myDevice->Init(myWindow->GetSDLWindow());
	}
}

bool VulkanEngine::LoadFunctions()
{
	if (!gVulkanInstance)
	{
		return false;
	}

	LOAD_VK_FUNCTION(vkEnumeratePhysicalDevices);
	LOAD_VK_FUNCTION(vkGetPhysicalDeviceProperties);
	LOAD_VK_FUNCTION(vkGetPhysicalDeviceFeatures);
	LOAD_VK_FUNCTION(vkGetPhysicalDeviceQueueFamilyProperties);
	LOAD_VK_FUNCTION(vkCreateDevice);
	LOAD_VK_FUNCTION(vkGetDeviceQueue);
	LOAD_VK_FUNCTION(vkGetPhysicalDeviceSurfaceSupportKHR);
	LOAD_VK_FUNCTION(vkGetPhysicalDeviceSurfaceCapabilitiesKHR);
	LOAD_VK_FUNCTION(vkGetPhysicalDeviceSurfaceFormatsKHR);
	LOAD_VK_FUNCTION(vkGetPhysicalDeviceSurfacePresentModesKHR);
	LOAD_VK_FUNCTION(vkCreateSwapchainKHR);
	LOAD_VK_FUNCTION(vkGetSwapchainImagesKHR);
	LOAD_VK_FUNCTION(vkCreateImageView);
	LOAD_VK_FUNCTION(vkCreateWin32SurfaceKHR);
	LOAD_VK_FUNCTION(vkCreateShaderModule);
	
	return true;
}

void VulkanEngine::Shutdown()
{
	if (myInstance)
	{
		delete myInstance;
	}

	if (myWindow)
	{
		myWindow->Close();
		delete myWindow;
	}

	if (myDevice)
	{
		delete myDevice;
	}
}

