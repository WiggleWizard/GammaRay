runtimeincludedirs = {}

local thirdpartydir = rootdir .. "/Runtime/Thirdparty"

group "Dependencies"
    include(thirdpartydir .. "/SDL_lib_p5.lua")
    include(thirdpartydir .. "/spdlog_p5.lua")
    include(thirdpartydir .. "/bgfx_p5.lua")
group ""

group "Projects"

project "Runtime"
    kind "StaticLib"
    language "C++"
    cppdialect "C++20"
    architecture "x64"
    staticruntime "On"
    
    targetdir("Build/Binaries/" .. outputdir)
    objdir("Build/Intermediate/" .. outputdir)
    
    pchheader "RuntimePCH.h"
    pchsource "Source/RuntimePCH.cpp"

    files
    {
        "Source/**.h",
        "Source/**.cpp",
    }
    
    includedirs
    {
        "Source"
    }
    
    externalincludedirs
    {
        thirdpartydir .. "/%{includedirectory.sdl2}",
        thirdpartydir .. "/%{includedirectory.spdlog}",
        
        path.join(thirdpartydir, "/%{public_includes.bgfx}"),
    }
    runtimeincludedirs["spdlog"] = thirdpartydir .. "/%{includedirectory.spdlog}"
    
    forceincludes
    {
        "RuntimePCH.h"
    }
    
    -- Just here as a placeholder for a feature I intend to add at some point
    runtimelinks = {
        "SDL2",
    }
    
    links
    {
        "SDL2",
        "spdlog",
        "bgfx"
    }
    
    defines
    {
        
    }
        
    filter { "system:windows", "action:vs*"}
        flags
        {
            "MultiProcessorCompile",
        }

    filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"

    filter "configurations:Release"
        defines { "NDEBUG" }
        optimize "On"
        
group ""