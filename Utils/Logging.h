#include "MemoryMacros.h"

void PrintToLog(const String& Category, const String& msg, ...);

#define LGO(LogCategory, msg, ...)
#define ensure(statement) [] (bool completes) { static bool hasEnsured = false; \
	if	(!completes && !hasEnsured)\
	{\
		hasEnsured = true;\
	}\
} \
