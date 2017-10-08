#include "SDLWindow.h"

#include "VulkanInstance.h"

#include <stdio.h>

void SDLWindow::CreateWindow(const WindowMode aWindowMode, const uint16 aWindowWidth, const uint16 aWindowHeight, VulkanInstance* Instance)
{
	uint32 WindowFlags = SDL_WINDOW_OPENGL;

	switch (aWindowMode)
	{
		case WindowMode::Fullscreen:
			WindowFlags = WindowFlags | SDL_WINDOW_FULLSCREEN;
			break;
		case WindowMode::Windowed:
			WindowFlags = WindowFlags | SDL_WINDOW_RESIZABLE;
			break;
		case WindowMode::BorderlessWindowed:
			WindowFlags = WindowFlags | SDL_WINDOW_BORDERLESS;
			break;
	}


	myWindow = SDL_CreateWindow("Cerberus", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, aWindowWidth, aWindowHeight, WindowFlags);
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

