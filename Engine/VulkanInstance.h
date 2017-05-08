#pragma once

#include "VulkanLoader.h"
#include "../Utils/Array.h"

class VulkanInstance
{
public:
	void Create();

	VkInstance VulkanInstance;
private:
	void LoadBaseFunctions();
	void CreateInstance();
	void CheckValidationLayerSupport();

	Array<VkLayerProperties> AvailableValidationLayers;

	bool bEnableValidationLayers;

	DEFINE_VKFUNCTIONPTR(vkCreateInstance);
	DEFINE_VKFUNCTIONPTR(vkEnumerateInstanceLayerProperties);
	DEFINE_VKFUNCTIONPTR(vkEnumerateInstanceExtensionProperties);
};