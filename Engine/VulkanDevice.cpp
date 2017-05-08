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
}

void VulkanDevice::GetDevices(Array<VkPhysicalDevice>& Devices)
{
	uint32 NumberOfDevices;
	myLoader->fpvkEnumeratePhysicalDevices(myInstance->VulkanInstance, &NumberOfDevices, NULL);
	printf("Found %d number of devices!\n", NumberOfDevices);

	Devices.InitEmpty(NumberOfDevices);
	myLoader->fpvkEnumeratePhysicalDevices(myInstance->VulkanInstance, &NumberOfDevices, Devices.Data());
}