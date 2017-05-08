#pragma once

#include "VulkanLoadMacros.h"
#include "../Utils/Array.h"

class VulkanInstance
{
public:
	void Create();

private:
	void LoadBaseFunctions();
	void CreateInstance();
	void CheckValidationLayerSupport();

	VkInstance VulkanInstance;
	Array<VkLayerProperties> AvailableValidationLayers;

	DEFINE_VKFUNCTIONPTR(vkCreateInstance);
	DEFINE_VKFUNCTIONPTR(vkEnumerateInstanceLayerProperties);
	DEFINE_VKFUNCTIONPTR(vkEnumerateInstanceExtensionProperties);
};