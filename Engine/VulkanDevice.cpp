#include "VulkanDevice.h"

#include "SDLWindow.h"
#include "VulkanLoader.h"
#include "VulkanInstance.h"

#include <stdio.h>

void VulkanDevice::Init(VulkanInstance* Instance, VulkanLoader* Loader, SDLWindow& Window)
{
	myInstance = Instance;
	myLoader = Loader;

	mySurface = Window.GetSurface();

	Array<VkPhysicalDevice> Devices;
	GetDevices(Devices);
	ChooseSuitableDevice(Devices);

	CreateDevice();
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
			myPhysicalDevice = PotentialDevice;
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
    	FamilyIndicies = Indices;
    	return Indices.IsComplete();
    }

    return false;
}

QueueFamilyIndices VulkanDevice::FindQueueFamilies(VkPhysicalDevice Device)
{
	QueueFamilyIndices Indices;

	uint32 QueueFamilyCount = 0;
	myLoader->fpvkGetPhysicalDeviceQueueFamilyProperties(Device, &QueueFamilyCount, nullptr);

	Array<VkQueueFamilyProperties> QueueFamilies;
	QueueFamilies.InitEmpty(QueueFamilyCount);
	myLoader->fpvkGetPhysicalDeviceQueueFamilyProperties(Device, &QueueFamilyCount, QueueFamilies.Data());

	int i = 0;
	for (const auto& QueueFamily : QueueFamilies)
	{
		VkBool32 PresentSupport = false;
		myLoader->fpvkGetPhysicalDeviceSurfaceSupportKHR(Device, i, mySurface, &PresentSupport);

		if (QueueFamily.queueCount > 0 && QueueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT && PresentSupport) 
		{
			Indices.GraphicsFamily = i;
			Indices.PresentFamily = i;
			break;
		}

		i++;
	}

	return Indices;
}

void VulkanDevice::CreateDevice()
{
	VkDeviceQueueCreateInfo QueueCreateInfo = {};
	QueueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
	QueueCreateInfo.queueFamilyIndex = FamilyIndicies.GraphicsFamily;
	QueueCreateInfo.queueCount = 1;

	float QueuePriority = 1.0f;
	QueueCreateInfo.pQueuePriorities = &QueuePriority;

	VkDeviceCreateInfo CreateInfo = {};
	CreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
	CreateInfo.pQueueCreateInfos = &QueueCreateInfo;
	CreateInfo.queueCreateInfoCount = 1;
	CreateInfo.pEnabledFeatures = &myDeviceFeatures;
	CreateInfo.enabledLayerCount = 0;

	Array<const int8*> DeviceExtensions;
	DeviceExtensions.Add(VK_KHR_SWAPCHAIN_EXTENSION_NAME);

	CreateInfo.enabledExtensionCount = DeviceExtensions.Num();
	CreateInfo.ppEnabledExtensionNames = DeviceExtensions.Data();

	VkResult result = myLoader->fpvkCreateDevice(myPhysicalDevice, &CreateInfo, NULL, &myDevice);
	if (result != VK_SUCCESS)
	{
		printf("Failed to create device");
		return;
	}

	myLoader->fpvkGetDeviceQueue(myDevice, FamilyIndicies.GraphicsFamily, 0, &myGraphicsQueue);
}