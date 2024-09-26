runtimeincludedirs = {}

local thirdpartydir = rootdir .. "/Runtime/Thirdparty"

group "Dependencies"
    include(thirdpartydir .. "/SDL_lib_p5.lua")
    include(thirdpartydir .. "/spdlog_p5.lua")
    include(thirdpartydir .. "/diligent_core_p5.lua")
    include(thirdpartydir .. "/diligent_tools_p5.lua")
    include(thirdpartydir .. "/imgui_p5.lua")
    
    build_data.project_declare["DiligentToolsImGui"]("ThirdParty")
    build_data.project_declare["ImGui"]("ThirdParty/DiligentTools/ThirdParty/imgui")
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
    
    DEGFX_Bind("ThirdParty/DiligentEngine")

    files
    {
        "Source/**.h",
        "Source/**.cpp",
    }
    
    includedirs
    {
        "Source",
        "ThirdParty/DiligentCore",
        table.unpack(build_data.project_public_includes["ImGui"]("ThirdParty/DiligentTools/ThirdParty/imgui")),
    }
    
    externalincludedirs
    {
        thirdpartydir .. "/%{includedirectory.sdl2}",
        thirdpartydir .. "/%{includedirectory.spdlog}",
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
        "glew",
        "DiligentToolsImGui",
        "ImGui"
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