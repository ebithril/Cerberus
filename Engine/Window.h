#pragma once

#include "EngineStructs.h"

class SDLWindow;

class Window
{
public:
	void CreateWindow(const WindowMode aWindowMode, const uint16 aWindowWidth, const uint16 aWindowHeight);
	void Close();

private:
	SDLWindow* myWindow;
};