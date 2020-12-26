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
