#include "Engine/Engine.h"

#include <stdio.h>

int main()
{
	EngineStartupOptions StartUpOptions;
	StartUpOptions.myWindowWidth = 640;
	StartUpOptions.myWindowHeight = 480;

	Engine myEngine;

	myEngine.Init(StartUpOptions);

	myEngine.Run();

	myEngine.ShutDown();

	return 0;
}