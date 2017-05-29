#pragma once 

#include <new>
#include <thread>
#include "MemoryTracker.h"

#define new (MemoryTracker::GetInstance()->Allocate(__LINE__, __FILE__, __FUNCTION__), false) ? 0 : new