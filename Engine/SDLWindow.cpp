#include "SDLWindow.h"

#include "VulkanInstance.h"
#include "VulkanLoader.h"

#include <stdio.h>

void SDLWindow::CreateWindow(const WindowMode aWindowMode, const uint16 aWindowWidth, const uint16 aWindowHeight, VulkanInstance* Instance, VulkanLoader* Loader)
{
	myWindow = SDL_CreateWindow("Cerberus", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, aWindowWidth, aWindowHeight, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
	if (!myWindow)
	{
		printf("Could not create window %s", SDL_GetError());
	}

	SDL_VERSION(&myWindowInfo.version);
	if (!SDL_GetWindowWMInfo(myWindow, &myWindowInfo))
	{
		printf("Something went wrong when getting window info\n");
	}

	VkWin32SurfaceCreateInfoKHR CreateInfo = {};
	CreateInfo.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
	CreateInfo.hwnd = myWindowInfo.info.win.window;
	CreateInfo.hinstance = GetModuleHandle(nullptr);

	DEFINE_VKFUNCTIONPTR(vkCreateWin32SurfaceKHR);
	LOAD_VULKAN_FUNCTION(Instance->VulkanInstance, vkCreateWin32SurfaceKHR);

	if (fpvkCreateWin32SurfaceKHR(Instance->VulkanInstance, &CreateInfo, nullptr, &VulkanSurface) != VK_SUCCESS)
	{
		printf("Failed to create surface \n");
	}
}

void SDLWindow::Close()
{
	if (myWindow)
	{
		SDL_DestroyWindow(myWindow);
		myWindow = nullptr;
		printf("Closed window!");
	}
}