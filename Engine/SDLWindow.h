#pragma once

#include "EngineStructs.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_syswm.h>

#include "VulkanInclude.h"

#undef CreateWindow

class VulkanInstance;
class VulkanLoader;

class SDLWindow
{
public:
	void CreateWindow(const WindowMode aWindowMode, const uint16 aWindowWidth, const uint16 aWindowHeight, VulkanInstance* Instance, VulkanLoader* Loader);
	void Close();

	VkSurfaceKHR GetSurface() { return VulkanSurface; }	

private:
	SDL_Window* myWindow;
	SDL_SysWMinfo myWindowInfo;

	VkSurfaceKHR VulkanSurface;
};