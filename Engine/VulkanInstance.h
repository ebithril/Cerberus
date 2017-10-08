#pragma once

#include "VulkanInclude.h"
#include <Array.h>

class VulkanInstance
{
public:
	void Create();

private:
	void LoadBaseFunctions();
	void CreateInstance();
	void CheckValidationLayerSupport();

	Array<VkLayerProperties> AvailableValidationLayers;
	bool bEnableValidationLayers;
};

