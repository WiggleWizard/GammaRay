#pragma once


#ifdef GR_PLATFORM_WINDOWS
    #ifdef GR_BUILD_DLL
        #define GAMMARAY_API __declspec(dllexport)
    #else
        #define GAMMARAY_API __declspec(dllimport)
    #endif
#else
    #error Windows only support!
#endif

#define BIT(x) (x << 1)

#ifdef GR_DEBUG
    #ifdef GR_PLATFORM_WINDOWS
        #define DEBUGBREAK __debugbreak()
    #endif
#else
    #define DEBUGBREAK
#endif

#ifdef GR_ENABLE_ASSERTS
    #define GR_CORE_ASSERT(condition, ...) if(!(condition)) { GR_CORE_ERROR(__VA_ARGS__); DEBUGBREAK; }
    #define GR_ASSERT(condition, ...) if(!(condition)) { GR_CLIENT_ERROR(__VA_ARGS__); DEBUGBREAK; }
#else
    #define GR_CORE_ASSERT(condition, ...)
    #define GR_ASSERT(condition, ...)
#endif
