#include "VulkanInstance.h"

#include "EngineStructs.h"
#include "VulkanLoader.h"

#include <stdio.h>

void VulkanInstance::Create()
{
	bEnableValidationLayers = false;

	LoadBaseFunctions();
	CheckValidationLayerSupport();

	CreateInstance();
}

void VulkanInstance::LoadBaseFunctions()
{
	LOAD_VULKAN_FUNCTION(NULL, vkCreateInstance);
	LOAD_VULKAN_FUNCTION(NULL, vkEnumerateInstanceLayerProperties);
	LOAD_VULKAN_FUNCTION(NULL, vkEnumerateInstanceExtensionProperties);
}

void VulkanInstance::CreateInstance()
{
	VkApplicationInfo appInfo = {};
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pApplicationName = "Cerberus";
    appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.pEngineName = "Cerberus";
    appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.apiVersion = VK_API_VERSION_1_0;

    VkInstanceCreateInfo createInfo = {};
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo = &appInfo;

   	Array<const int8*> Extensions;
   	Extensions.Add("VK_KHR_surface");
   	Extensions.Add("VK_KHR_win32_surface");
   	
   	createInfo.enabledExtensionCount = Extensions.Num();
   	createInfo.ppEnabledExtensionNames = Extensions.Data();

    createInfo.enabledLayerCount = 0;

    VkResult result = fpvkCreateInstance(&createInfo, nullptr, &VulkanInstance);

	if (result != VK_SUCCESS)
	{
		printf("Failed to create vulkan instance\n");
	}
}

void VulkanInstance::CheckValidationLayerSupport()
{
	if (!bEnableValidationLayers)
	{
		return;
	}

	uint32 LayerCount;
	fpvkEnumerateInstanceLayerProperties(&LayerCount, NULL);

	AvailableValidationLayers.InitEmpty(LayerCount);
	fpvkEnumerateInstanceLayerProperties(&LayerCount, AvailableValidationLayers.Data());

	for (VkLayerProperties& Layer : AvailableValidationLayers)
	{
		printf("Name: %s\n", Layer.layerName);
		printf("Description: %s\n\n", Layer.description);
	}
}