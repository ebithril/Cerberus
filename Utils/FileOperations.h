#pragma once

#include "Types.h"
#include "MemoryMacros.h"
#include "Array.h"

class String;

void ReadFileIntoArray(const String& FileName, Array<int8>& outArray);
