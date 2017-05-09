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
	void CreateDevice();

	QueueFamilyIndices FindQueueFamilies(VkPhysicalDevice Device);

	VulkanInstance* myInstance;
	VulkanLoader* myLoader;

	VkPhysicalDevice myPhysicalDevice;
	VkPhysicalDeviceProperties myDeviceProperties;
	VkPhysicalDeviceFeatures myDeviceFeatures;

	QueueFamilyIndices FamilyIndicies;

	VkDevice myDevice;
	VkQueue myGraphicsQueue;
};