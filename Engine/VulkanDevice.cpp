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
	SetupSwapChain();
	SetupSwapChainImageViews();
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

void VulkanDevice::SetupSwapChain()
{
	SwapChainSupportDetails Details;

	myLoader->fpvkGetPhysicalDeviceSurfaceCapabilitiesKHR(myPhysicalDevice, mySurface, &Details.Capabilities);

	uint32 FormatCount;
	myLoader->fpvkGetPhysicalDeviceSurfaceFormatsKHR(myPhysicalDevice, mySurface, &FormatCount, NULL);

	if (FormatCount	<= 0)
	{
		printf("Something went wrong there are no format counts supported.\n");
		return;
	}

	Details.Formats.InitEmpty(FormatCount);
	myLoader->fpvkGetPhysicalDeviceSurfaceFormatsKHR(myPhysicalDevice, mySurface, &FormatCount, Details.Formats.Data());

	uint32 PresentModeCount;
	myLoader->fpvkGetPhysicalDeviceSurfacePresentModesKHR(myPhysicalDevice, mySurface, &PresentModeCount, NULL);

	if (PresentModeCount <= 0)
	{
		printf("Something went wrong there are no Present modes supproted.\n");
		return;
	}

	Details.PresentModes.InitEmpty(PresentModeCount);
	myLoader->fpvkGetPhysicalDeviceSurfacePresentModesKHR(myPhysicalDevice, mySurface, &PresentModeCount, Details.PresentModes.Data());

	mySurfaceFormat = ChooseSwapSurfaceFormat(Details.Formats);
	mySurfacePresentMode = ChooseSwapPresentMode(Details.PresentModes);
	mySwapExtent = ChooseSwapExtent(Details.Capabilities);

	uint32 ImageCount = Details.Capabilities.minImageCount + 1;
	if (Details.Capabilities.maxImageCount > 0 && ImageCount > Details.Capabilities.maxImageCount)
	{
		ImageCount = Details.Capabilities.maxImageCount;
	}

	VkSwapchainCreateInfoKHR CreateInfo = {};
	CreateInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
	CreateInfo.surface = mySurface;
	CreateInfo.minImageCount = ImageCount;
	CreateInfo.imageFormat = mySurfaceFormat.format;
	CreateInfo.imageColorSpace = mySurfaceFormat.colorSpace;
	CreateInfo.imageExtent = mySwapExtent;
	CreateInfo.imageArrayLayers = 1;
	CreateInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
	CreateInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
    CreateInfo.queueFamilyIndexCount = 0; // Optional
    CreateInfo.pQueueFamilyIndices = nullptr; // Optional
    CreateInfo.preTransform = Details.Capabilities.currentTransform;
    CreateInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
    CreateInfo.presentMode = mySurfacePresentMode;
	CreateInfo.clipped = VK_TRUE;
	CreateInfo.oldSwapchain = VK_NULL_HANDLE;

	if (myLoader->fpvkCreateSwapchainKHR(myDevice, &CreateInfo, NULL, &mySwapChain) != VK_SUCCESS)
	{
		printf("Failed to create swap chain.\n");
		return;
	}

	myLoader->fpvkGetSwapchainImagesKHR(myDevice, mySwapChain, &ImageCount, NULL);
	mySwapChainImages.InitEmpty(ImageCount);
	myLoader->fpvkGetSwapchainImagesKHR(myDevice, mySwapChain, &ImageCount, mySwapChainImages.Data());
}

VkSurfaceFormatKHR VulkanDevice::ChooseSwapSurfaceFormat(const Array<VkSurfaceFormatKHR>& AvailableFormats)
{
	if (AvailableFormats.Num() == 1 && AvailableFormats[0].format == VK_FORMAT_UNDEFINED)
	{
		return {VK_FORMAT_B8G8R8A8_UNORM, VK_COLOR_SPACE_SRGB_NONLINEAR_KHR};
	}

	for (const VkSurfaceFormatKHR& AvailableFormat : AvailableFormats)
	{
		if (AvailableFormat.format == VK_FORMAT_B8G8R8A8_UNORM && AvailableFormat.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR)
		{
			return AvailableFormat;
		}
	}

	return AvailableFormats[0];
}

VkPresentModeKHR VulkanDevice::ChooseSwapPresentMode(const Array<VkPresentModeKHR>& AvailablePresentModes)
{
	VkPresentModeKHR BestMode = VK_PRESENT_MODE_FIFO_KHR;

	for (const VkPresentModeKHR& AvailablePresentMode : AvailablePresentModes)
	{
		if (AvailablePresentMode == VK_PRESENT_MODE_MAILBOX_KHR)
		{
			return VK_PRESENT_MODE_MAILBOX_KHR;
		}
		else if (AvailablePresentMode == VK_PRESENT_MODE_IMMEDIATE_KHR)
		{
			BestMode = AvailablePresentMode;
		}
	}

	return BestMode;
}

VkExtent2D VulkanDevice::ChooseSwapExtent(const VkSurfaceCapabilitiesKHR& Capabilities)
{
	return Capabilities.currentExtent;
}

void VulkanDevice::SetupSwapChainImageViews()
{
	mySwapChainImageViews.InitEmpty(mySwapChainImages.Num());

	for (int32 i = 0; i < mySwapChainImageViews.Num(); ++i)
	{
		VkImageViewCreateInfo CreateInfo = {};

		CreateInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
		CreateInfo.image = mySwapChainImages[i];
		CreateInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
		CreateInfo.format = mySurfaceFormat.format;
		CreateInfo.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
		CreateInfo.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
		CreateInfo.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
		CreateInfo.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;
		CreateInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
		CreateInfo.subresourceRange.baseMipLevel = 0;
		CreateInfo.subresourceRange.levelCount = 1;
		CreateInfo.subresourceRange.baseArrayLayer = 0;
		CreateInfo.subresourceRange.layerCount = 1;

		if (myLoader->fpvkCreateImageView(myDevice, &CreateInfo, NULL, &mySwapChainImageViews[i]) != VK_SUCCESS)
		{
			printf("Failed to create image view for swap chain");
			return;
		}
	}
}
