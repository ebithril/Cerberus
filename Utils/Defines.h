#pragma once

#if defined _WIN32
#define PLATFORM_WINDOWS
#elif defined __linux__
#define PLATFORM_LINUX
#else
#error "Platform isn't supported yet"
#endif
