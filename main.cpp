#include <MemoryMacros.h>
#include <Engine.h>

#include <stdio.h>

int main()
{
	MemoryTracker::Create();

	EngineStartupOptions StartUpOptions;
	StartUpOptions.myWindowWidth = 1280;
	StartUpOptions.myWindowHeight = 720;
	StartUpOptions.myWindowMode = WindowMode::Windowed;

	Engine myEngine;

	myEngine.Init(StartUpOptions);

	myEngine.Run();

	myEngine.ShutDown();

	MemoryTracker::Destroy();
	return 0;
}
