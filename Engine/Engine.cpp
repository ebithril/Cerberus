#include "Engine.h"

#include "Window.h"
#include "VulkanEngine.h"

#include "Include/SDL2/SDL.h"

#include <stdio.h>

void Engine::Init(const EngineStartupOptions& StartUpOptions)
{
	myWindow = new Window();

	if (myWindow)
	{
		myWindow->CreateWindow(StartUpOptions.myWindowMode, StartUpOptions.myWindowWidth, StartUpOptions.myWindowHeight);
	}

	myEngine = new VulkanEngine();
	if (myEngine)
	{
		myEngine->InitVulkan();
	}
}

void Engine::Run()
{
	const uint8* KeyboardState = SDL_GetKeyboardState(nullptr);
	bool bShutdown = false;

	while(!bShutdown)
	{
		SDL_PumpEvents();

		if (KeyboardState[SDL_SCANCODE_ESCAPE])
		{
			printf("Escape pressed exiting\n");
			bShutdown = true;
		}

		SDL_Event event;
		while(SDL_PollEvent(&event))
		{
			if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE)
			{
				printf("Closed window shutting down\n");
				bShutdown = true;
			}
		}
	}
}

void Engine::ShutDown()
{
	if (myWindow)
	{
		myWindow->Close();
		delete myWindow;
	}

	if (myEngine)
	{
		delete myEngine;
	}
}