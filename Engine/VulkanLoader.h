#pragma once

#include "EngineStructs.h"
#include "Include/vulkan/vulkan.h"
#include "VulkanLoadMacros.h"

class VulkanLoader
{
public:
	void LoadFunctions();

	static PFN_vkGetInstanceProcAddr vkGetProcAddress;

private:
};