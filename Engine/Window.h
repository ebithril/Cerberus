#pragma once

#include "EngineStructs.h"

#undef CreateWindow

class VulkanInstance;
class VulkanLoader;
class SDLWindow;

class Window
{
public:
	void CreateWindow(const WindowMode aWindowMode, const uint16 aWindowWidth, const uint16 aWindowHeight, VulkanInstance* Instance, VulkanLoader* Loader);
	void Close();

	SDLWindow& GetSDLWindow() { return *myWindow; }

private:
	SDLWindow* myWindow;
};