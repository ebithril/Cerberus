#pragma once

#include "EngineStructs.h"

#undef CreateWindow

class VulkanInstance;
class SDLWindow;

class Window
{
public:
	void CreateWindow(const WindowMode aWindowMode, const uint16 aWindowWidth, const uint16 aWindowHeight, VulkanInstance* Instance);
	void Close();

	SDLWindow& GetSDLWindow() { return *myWindow; }

private:
	SDLWindow* myWindow = nullptr;
};
