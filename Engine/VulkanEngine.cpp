#include "VulkanEngine.h"

#include "VulkanInstance.h"
#include "VulkanLoader.h"
#include "VulkanDevice.h"

#include <windows.h>

void VulkanEngine::InitVulkan()
{
	VulkanLoader::vkGetProcAddress = (PFN_vkGetInstanceProcAddr)GetProcAddress(LoadLibrary("vulkan-1.dll"), "vkGetInstanceProcAddr");

	myInstance = new VulkanInstance();
	if (myInstance)
	{
		myInstance->Create();
	}

	myLoader = new VulkanLoader();
	if (myLoader)
	{
		myLoader->Init(myInstance);
		myLoader->LoadFunctions();
	}

	myDevice = new VulkanDevice();
	if (myDevice)
	{
		myDevice->Init(myInstance, myLoader);
	}
}