#pragma once

class VulkanInstance;
class VulkanLoader;
class VulkanDevice;
class Window;

struct EngineStartupOptions;

class VulkanEngine
{
public:
	void InitVulkan(const EngineStartupOptions& StartUpOptions);

private:
	VulkanInstance* myInstance;
	VulkanLoader* myLoader;
	VulkanDevice* myDevice;

	Window* myWindow;
};