#pragma once

#include "EngineStructs.h"

class VulkanEngine;

class Engine
{
public:
	void Init(const EngineStartupOptions& StartUpOptions);
	void Run();
	void ShutDown();

private:
	VulkanEngine* myEngine;
};