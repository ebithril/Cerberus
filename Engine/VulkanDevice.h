#pragma once

class VulkanInstance;
class VulkanLoader;

#include "../utils/Array.h"
#include "include/vulkan/vulkan.h"

class VulkanDevice
{
public:
	void Init(VulkanInstance* Instance, VulkanLoader* Loader);

private:
	void GetDevices(Array<VkPhysicalDevice>& Devices);

	VulkanInstance* myInstance;
	VulkanLoader* myLoader;
};