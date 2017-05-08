#include "SDLWindow.h"

#include <stdio.h>

void SDLWindow::CreateWindow(const WindowMode aWindowMode, const uint16 aWindowWidth, const uint16 aWindowHeight)
{
	myWindow = SDL_CreateWindow("Cerberus", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, aWindowWidth, aWindowHeight, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
	if (!myWindow)
	{
		printf("Could not create window %s", SDL_GetError());
	}

	if (!SDL_GetWindowWMInfo(myWindow, &myWindowInfo))
	{
		printf("Something went wrong when getting window info\n");
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