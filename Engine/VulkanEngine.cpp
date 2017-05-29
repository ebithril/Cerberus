#include "VulkanEngine.h"

#include <windows.h>

#include "Window.h"
#include "VulkanInstance.h"
#include "VulkanLoader.h"
#include "VulkanDevice.h"


void VulkanEngine::InitVulkan(const EngineStartupOptions& StartUpOptions)
{
	VulkanLoader::vkGetProcAddress = (PFN_vkGetInstanceProcAddr)GetProcAddress(LoadLibrary("vulkan-1.dll"), "vkGetInstanceProcAddr");

	myInstance = new VulkanInstance();
	if (myInstance)
	{
		myInstance->Create();
	}

	myLoader = new VulkanLoader();
	if (myLoader)
	{
		myLoader->Init(myInstance);
		myLoader->LoadFunctions();
	}

	myWindow = new Window();
	if (myWindow)
	{
		myWindow->CreateWindow(StartUpOptions.myWindowMode, StartUpOptions.myWindowWidth, StartUpOptions.myWindowHeight, myInstance, myLoader);
	}

	myDevice = new VulkanDevice();
	if (myDevice)
	{
		myDevice->Init(myInstance, myLoader, myWindow->GetSDLWindow());
	}
}

void VulkanEngine::Shutdown()
{
	if (myInstance)
	{
		delete myInstance;
	}

	if (myLoader)
	{
		delete myLoader;
	}

	if (myWindow)
	{
		delete myWindow;
	}

	if (myDevice)
	{
		delete myDevice;
	}
}