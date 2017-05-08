#pragma once

#include "EngineStructs.h"

#include "Include/SDL2/SDL.h"
#include "Include/SDL2/SDL_syswm.h"

#undef CreateWindow

class SDLWindow
{
public:
	void CreateWindow(const WindowMode aWindowMode, const uint16 aWindowWidth, const uint16 aWindowHeight);
	void Close();

private:
	SDL_Window* myWindow;
	SDL_SysWMinfo myWindowInfo;
};