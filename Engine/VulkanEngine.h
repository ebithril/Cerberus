#pragma once

class VulkanInstance;
class VulkanLoader;
class VulkanDevice;

class VulkanEngine
{
public:
	void InitVulkan();

private:
	VulkanInstance* myInstance;
	VulkanLoader* myLoader;
	VulkanDevice* myDevice;
};