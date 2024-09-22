local deprootpath = "SDL2"
local includedirectoryname = "sdl2"
local includedir = deprootpath .. "/include"

project "SDL2"
    location "SDL2"
    kind "StaticLib"
    staticruntime "on"
    language "C++"
    architecture "x64"
    
    targetdir (deprootpath .. "/Build/Binaries/" .. outputdir)
    objdir (deprootpath .. "/Build/Intermediate/" .. outputdir)
    
    flags {
        "NoRuntimeChecks", -- Only used on Visual Studio.
        "NoBufferSecurityCheck"
    }
    
    includedirectory[includedirectoryname] = includedir
    
    includedirs
    {
        includedir
    }
    
    files
    {
        includedir .. "/*.h",
        deprootpath .. "/src/*.c",
        
        deprootpath .. "/src/audio/disk/*.h",     deprootpath .. "/src/atomic/*.c",
        deprootpath .. "/src/audio/dummy/*.h",    deprootpath .. "/src/audio/disk/*.c",
        deprootpath .. "/src/audio/*.h",          deprootpath .. "/src/audio/dummy/*.c",
        deprootpath .. "/src/dynapi/*.h",         deprootpath .. "/src/audio/*.c",
        
        deprootpath .. "/src/events/blank_cursor.h",              deprootpath .. "/src/cpuinfo/*.c",
        deprootpath .. "/src/events/default_cursor.h",            deprootpath .. "/src/dynapi/*.c",
        deprootpath .. "/src/events/SDL_clipboardevents_c.h",     deprootpath .. "/src/events/*.c",
        deprootpath .. "/src/events/SDL_displayevents_c.h",       deprootpath .. "/src/file/*.c",
        deprootpath .. "/src/events/SDL_dropevents_c.h",          deprootpath .. "/src/haptic/*.c",
        deprootpath .. "/src/events/SDL_events_c.h",              deprootpath .. "/src/joystick/hidapi/*.c",
        deprootpath .. "/src/events/SDL_gesture_c.h",             deprootpath .. "/src/joystick/*.c",
        deprootpath .. "/src/events/SDL_keyboard_c.h",            deprootpath .. "/src/libm/*.c",
        deprootpath .. "/src/events/SDL_mouse_c.h",               deprootpath .. "/src/power/*.c",
        deprootpath .. "/src/events/SDL_sysevents.h",             deprootpath .. "/src/render/opengl/*.c",
        deprootpath .. "/src/events/SDL_touch_c.h",               deprootpath .. "/src/render/opengles2/*.c",
        deprootpath .. "/src/events/SDL_windowevents_c.h",        deprootpath .. "/src/render/SDL_render.c",
        deprootpath .. "/src/haptic/SDL_syshaptic.h",             deprootpath .. "/src/render/SDL_yuv_sw.c",
        deprootpath .. "/src/joystick/hidapi/*.h",                deprootpath .. "/src/render/software/*.c",
        deprootpath .. "/src/joystick/SDL_hidapijoystick_c.h",    deprootpath .. "/src/sensor/dummy/SDL_dummysensor.c",
        deprootpath .. "/src/joystick/SDL_joystick_c.h",          deprootpath .. "/src/sensor/SDL_sensor.c",
        deprootpath .. "/src/joystick/SDL_sysjoystick.h",         deprootpath .. "/src/stdlib/*.c",
        deprootpath .. "/src/libm/*.h",                           deprootpath .. "/src/thread/generic/SDL_syscond.c",
        deprootpath .. "/src/render/opengl/*.h",                  deprootpath .. "/src/thread/*.c",
        deprootpath .. "/src/render/opengles/*.h",                deprootpath .. "/src/thread/windows/SDL_sysmutex.c",
        deprootpath .. "/src/render/SDL_yuv_sw_c.h",              deprootpath .. "/src/thread/windows/SDL_syssem.c",
        deprootpath .. "/src/render/software/*.h",                deprootpath .. "/src/thread/windows/SDL_systhread.c",
        deprootpath .. "/src/render/SDL_sysrender.h",             deprootpath .. "/src/thread/windows/SDL_systls.c",
        deprootpath .. "/src/SDL_dataqueue.h",                    deprootpath .. "/src/timer/*.c",
        deprootpath .. "/src/SDL_error_c.h",                      deprootpath .. "/src/timer/windows/SDL_systimer.c",
        deprootpath .. "/src/sensor/dummy/*.h",                   deprootpath .. "/src/video/dummy/*.c",
        deprootpath .. "/src/sensor/*.h",                         deprootpath .. "/src/video/*.c",
        deprootpath .. "/src/thread/*.h",                         deprootpath .. "/src/video/yuv2rgb/*.c",
        deprootpath .. "/src/timer/*.h",
        deprootpath .. "/src/video/dummy/*.h",
        deprootpath .. "/src/video/*.h",
    }
    
    filter "system:windows"
        links
        {
            "setupapi",
            "winmm",
            "imm32",
            "version",
        }
    
    filter "system:windows"
        files {
            deprootpath .. "/src/main/windows/SDL_windows_main.c",
            deprootpath .. "/src/core/windows/*.c",
            deprootpath .. "/include/SDL_config_windows.h",				    
                
            deprootpath .. "/src/audio/directsound/*.h",                          deprootpath .. "/src/audio/directsound/*.c",
            deprootpath .. "/src/audio/wasapi/*.h",                               deprootpath .. "/src/audio/winmm/*.c",
            deprootpath .. "/src/audio/winmm/*.h",                                deprootpath .. "/src/audio/wasapi/*.c",
                                                                  
            deprootpath .. "/src/core/windows/*.h",                               deprootpath .. "/src/filesystem/windows/*.c",
            deprootpath .. "/src/haptic/windows/*.h",                             deprootpath .. "/src/haptic/windows/*.c",
            deprootpath .. "/src/joystick/windows/*.h",                           deprootpath .. "/src/joystick/windows/*.c",
            deprootpath .. "/src/render/direct3d11/SDL_shaders_d3d11.h",          deprootpath .. "/src/hidapi/windows/*.c",
            deprootpath .. "/src/render/direct3d/*.h",                            deprootpath .. "/src/loadso/windows/*.c",
            deprootpath .. "/src/render/SDL_d3dmath.h",                           deprootpath .. "/src/power/windows/*.c",
            deprootpath .. "/src/thread/windows/*.h",                             deprootpath .. "/src/render/direct3d11/*.c",
            deprootpath .. "/src/video/windows/SDL_vkeys.h",                      deprootpath .. "/src/render/direct3d/*.c",
            deprootpath .. "/src/video/windows/SDL_windowsclipboard.h",           deprootpath .. "/src/render/SDL_d3dmath.c",
            deprootpath .. "/src/video/windows/SDL_windowsevents.h",              deprootpath .. "/src/video/windows/*.c",
            deprootpath .. "/src/video/windows/SDL_windowsframebuffer.h",
            deprootpath .. "/src/video/windows/SDL_windowskeyboard.h",
            deprootpath .. "/src/video/windows/SDL_windowsmessagebox.h",
            deprootpath .. "/src/video/windows/SDL_windowsmodes.h",
            deprootpath .. "/src/video/windows/SDL_windowsmouse.h",
            deprootpath .. "/src/video/windows/SDL_windowsopengl.h",
            deprootpath .. "/src/video/windows/SDL_windowsshape.h",
            deprootpath .. "/src/video/windows/SDL_windowsvideo.h",
            deprootpath .. "/src/video/windows/SDL_windowsvulkan.h",
            deprootpath .. "/src/video/windows/SDL_windowswindow.h",
            deprootpath .. "/src/video/windows/wmmsg.h",
        }

    inlining "Explicit"
    intrinsics "Off"

    filter "system:windows"
        systemversion "latest"
        defines {
            "_WINDOWS",
            "SDL_VIDEO_DRIVER_WINDOWS"
        }

    filter "configurations:Debug"
        defines {
            "_DEBUG"
        }
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        defines {
            "NDEBUG"
        }
        runtime  "Release"
        optimize "Speed"


    filter "configurations:Development"     -- These are the configurations I tend to
        defines {                           -- use in my projects, but I have added 
            "NDEBUG"              -- the default ones anyway.
        }
        runtime  "Release"
        optimize "On"

    filter "configurations:Ship"
        defines {
            "NDEBUG"
        }
        runtime  "Release"
        optimize "Speed"