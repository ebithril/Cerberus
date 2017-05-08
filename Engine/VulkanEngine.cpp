#include "VulkanEngine.h"

#include "VulkanInstance.h"
#include "VulkanLoader.h"

#include <windows.h>

void VulkanEngine::InitVulkan()
{
	VulkanLoader::vkGetProcAddress = (PFN_vkGetInstanceProcAddr)GetProcAddress(LoadLibrary("vulkan-1.dll"), "vkGetInstanceProcAddr");

	myInstance = new VulkanInstance();
	if (myInstance)
	{
		myInstance->Create();
	}

}