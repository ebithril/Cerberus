#include "VulkanDevice.h"

#include "VulkanLoader.h"
#include "VulkanInstance.h"

#include <stdio.h>

void VulkanDevice::Init(VulkanInstance* Instance, VulkanLoader* Loader)
{
	myInstance = Instance;
	myLoader = Loader;

	Array<VkPhysicalDevice> Devices;
	GetDevices(Devices);
	ChooseSuitableDevice(Devices);
}

void VulkanDevice::GetDevices(Array<VkPhysicalDevice>& Devices)
{
	uint32 NumberOfDevices;
	myLoader->fpvkEnumeratePhysicalDevices(myInstance->VulkanInstance, &NumberOfDevices, NULL);
	printf("Found %d number of devices!\n", NumberOfDevices);

	Devices.InitEmpty(NumberOfDevices);
	myLoader->fpvkEnumeratePhysicalDevices(myInstance->VulkanInstance, &NumberOfDevices, Devices.Data());
}

void VulkanDevice::ChooseSuitableDevice(Array<VkPhysicalDevice>& Devices)
{
	for (VkPhysicalDevice& PotentialDevice : Devices)
	{
		if (IsDeviceSuitable(PotentialDevice, myDeviceProperties, myDeviceFeatures))
		{
			myDevice = PotentialDevice;
			printf("Chose device with name: %s\n", myDeviceProperties.deviceName);
			return;
		}
	}

	printf("Found no suitable device.");
}

bool VulkanDevice::IsDeviceSuitable(VkPhysicalDevice Device, VkPhysicalDeviceProperties& DeviceProperties, VkPhysicalDeviceFeatures& DeviceFeatures)
{
    myLoader->fpvkGetPhysicalDeviceProperties(Device, &DeviceProperties);
    myLoader->fpvkGetPhysicalDeviceFeatures(Device, &DeviceFeatures);

    if (DeviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU && DeviceFeatures.geometryShader)
    {
    	QueueFamilyIndices Indices = FindQueueFamilies(Device);
    	return Indices.IsComplete();
    }

    return false;
}

QueueFamilyIndices VulkanDevice::FindQueueFamilies(VkPhysicalDevice Device)
{
	QueueFamilyIndices Indices;

	uint32_t QueueFamilyCount = 0;
	myLoader->fpvkGetPhysicalDeviceQueueFamilyProperties(Device, &QueueFamilyCount, nullptr);

	Array<VkQueueFamilyProperties> QueueFamilies;
	QueueFamilies.InitEmpty(QueueFamilyCount);
	myLoader->fpvkGetPhysicalDeviceQueueFamilyProperties(Device, &QueueFamilyCount, QueueFamilies.Data());

	int i = 0;
	for (const auto& QueueFamily : QueueFamilies)
	{
		if (QueueFamily.queueCount > 0 && QueueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT) 
		{
			Indices.GraphicsFamily = i;
			break;
		}

		i++;
	}

	return Indices;
}
