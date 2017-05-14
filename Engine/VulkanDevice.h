#pragma once

class VulkanInstance;
class VulkanLoader;
class SDLWindow;

#include "../utils/Array.h"
#include "VulkanInclude.h"

struct QueueFamilyIndices
{
	int32 GraphicsFamily = -1;
	int32 PresentFamily = -1;

	bool IsComplete()
	{
		return GraphicsFamily >= 0 && PresentFamily >= 0;
	}
};

class VulkanDevice
{
public:
	void Init(VulkanInstance* Instance, VulkanLoader* Loader, SDLWindow& Window);

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
	VkSurfaceKHR mySurface;
};