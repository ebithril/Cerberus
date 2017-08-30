#include "MemoryMacros.h"

#include <signal.h>

class String;

void PrintToLog(const String& Category, const String& msg, ...);

#define LOG(LogCategory)
#define ensure(statement) (statement)

