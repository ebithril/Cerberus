#pragma once

class VulkanInstance;
class VulkanDevice;
class CerberusWindow;

struct EngineStartupOptions;

class VulkanEngine
{
public:
	void InitVulkan(const EngineStartupOptions& StartUpOptions);
	void Shutdown();
	
private:
	bool LoadFunctions();

	VulkanInstance* myInstance;
	VulkanDevice* myDevice;

	CerberusWindow* myWindow;
};

