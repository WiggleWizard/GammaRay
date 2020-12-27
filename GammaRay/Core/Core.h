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

// Should always inline no matter what.
#ifndef _ALWAYS_INLINE_
    #if defined(__GNUC__)
        #define _ALWAYS_INLINE_ __attribute__((always_inline)) inline
    #elif defined(_MSC_VER)
        #define _ALWAYS_INLINE_ __forceinline
    #else
        #define _ALWAYS_INLINE_ inline
    #endif
#endif

// Should always inline, except in debug builds because it makes debugging harder.
#ifndef _FORCE_INLINE_
    #ifdef DISABLE_FORCED_INLINE
        #define _FORCE_INLINE_ inline
    #else
        #define _FORCE_INLINE_ _ALWAYS_INLINE_
    #endif
#endif
