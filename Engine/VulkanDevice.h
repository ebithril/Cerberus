#pragma once

class SDLWindow;

#include <Array.h>
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

struct SwapChainSupportDetails
{
	VkSurfaceCapabilitiesKHR Capabilities;
	Array<VkSurfaceFormatKHR> Formats;
	Array<VkPresentModeKHR> PresentModes;
};

class VulkanDevice
{
public:
	void Init(SDLWindow& Window);

private:
	void GetDevices(Array<VkPhysicalDevice>& Devices);
	void ChooseSuitableDevice(Array<VkPhysicalDevice>& Devices);
	bool IsDeviceSuitable(VkPhysicalDevice Device, VkPhysicalDeviceProperties& DeviceProperties, VkPhysicalDeviceFeatures& DeviceFeatures);
	void CreateDevice();
	void SetupSwapChain();
	void SetupSwapChainImageViews();

	VkSurfaceFormatKHR ChooseSwapSurfaceFormat(const Array<VkSurfaceFormatKHR>& AvailableFormats);
	VkPresentModeKHR ChooseSwapPresentMode(const Array<VkPresentModeKHR>& AvailablePresentModes);
	VkExtent2D ChooseSwapExtent(const VkSurfaceCapabilitiesKHR& Capabilities);

	QueueFamilyIndices FindQueueFamilies(VkPhysicalDevice Device);

	VkPhysicalDevice myPhysicalDevice;
	VkPhysicalDeviceProperties myDeviceProperties;
	VkPhysicalDeviceFeatures myDeviceFeatures;

	QueueFamilyIndices FamilyIndicies;

	VkDevice myDevice;
	VkQueue myGraphicsQueue;
	VkSurfaceKHR mySurface;

	VkSwapchainKHR mySwapChain;
	Array<VkImage> mySwapChainImages;
	Array<VkImageView> mySwapChainImageViews;

	VkSurfaceFormatKHR mySurfaceFormat;
	VkPresentModeKHR mySurfacePresentMode;
	VkExtent2D mySwapExtent;
};

