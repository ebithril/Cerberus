#pragma once

#include "../Utils/Types.h"

enum class WindowMode : uint8
{
	Fullscreen,
	Windowed,
	BorderlessWindowed
};

struct EngineStartupOptions
{
	WindowMode myWindowMode;
	uint16 myWindowHeight;
	uint16 myWindowWidth;
};