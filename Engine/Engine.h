#pragma once

#include "EngineStructs.h"

class Window;
class VulkanEngine;

class Engine
{
public:
	void Init(const EngineStartupOptions& StartUpOptions);
	void Run();
	void ShutDown();

private:
	Window* myWindow;
	VulkanEngine* myEngine;
};