#pragma once

class VulkanInstance;
class VulkanLoader;

#include "../utils/Array.h"
#include "include/vulkan/vulkan.h"

struct QueueFamilyIndices
{
	int GraphicsFamily = -1;

	bool IsComplete()
	{
		return GraphicsFamily >= 0;
	}
};

class VulkanDevice
{
public:
	void Init(VulkanInstance* Instance, VulkanLoader* Loader);

private:
	void GetDevices(Array<VkPhysicalDevice>& Devices);
	void ChooseSuitableDevice(Array<VkPhysicalDevice>& Devices);
	bool IsDeviceSuitable(VkPhysicalDevice Device, VkPhysicalDeviceProperties& DeviceProperties, VkPhysicalDeviceFeatures& DeviceFeatures);

	QueueFamilyIndices FindQueueFamilies(VkPhysicalDevice Device);

	VulkanInstance* myInstance;
	VulkanLoader* myLoader;

	VkPhysicalDevice myDevice;
	VkPhysicalDeviceProperties myDeviceProperties;
	VkPhysicalDeviceFeatures myDeviceFeatures;

};