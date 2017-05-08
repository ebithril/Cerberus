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

   	createInfo.enabledExtensionCount = 0;
   	createInfo.ppEnabledExtensionNames = NULL;

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

	uint32 layerCount;
	fpvkEnumerateInstanceLayerProperties(&layerCount, NULL);

	AvailableValidationLayers.InitEmpty(layerCount);
	fpvkEnumerateInstanceLayerProperties(&layerCount, AvailableValidationLayers.Data());

	for (VkLayerProperties& layer : AvailableValidationLayers)
	{
		printf("Name: %s\n", layer.layerName);
		printf("Description: %s\n\n", layer.description);
	}
}