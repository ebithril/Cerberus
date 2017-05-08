#pragma once

class VulkanInstance;

class VulkanEngine
{
public:
	void InitVulkan();

private:
	VulkanInstance* myInstance;

};