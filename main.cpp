#include <Engine.h>

#include <stdio.h>

int main()
{
	EngineStartupOptions StartUpOptions;
	StartUpOptions.myWindowWidth = 1280;
	StartUpOptions.myWindowHeight = 720;

	Engine myEngine;

	myEngine.Init(StartUpOptions);

	myEngine.Run();

	myEngine.ShutDown();

	return 0;
}