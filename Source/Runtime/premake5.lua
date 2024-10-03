runtimeincludedirs = {}

local thirdpartydir = path.join(rootdir, "/Runtime/Thirdparty")

group "Dependencies"
    include(thirdpartydir .. "/spdlog_p5.lua")
    include(thirdpartydir .. "/SDL_lib_p5.lua")
    include(thirdpartydir .. "/diligent_core_p5.lua")
    include(thirdpartydir .. "/diligent_tools_p5.lua")
    include(thirdpartydir .. "/imgui_p5.lua")
    
    build_data.project_configure["spdlog"]("ThirdParty/spdlog")
    
    build_data.project_configure["SDL2"]("ThirdParty/SDL2")
    
    build_data.project_configure["SDL2"]("ThirdParty/SDL2")
    build_data.project_configure["DiligentCore"]("ThirdParty/DiligentCore")
    build_data.project_configure["ImGui"]("ThirdParty/DiligentTools/ThirdParty/imgui", table.unpack(build_data.project_public_includes["SDL2"]()))
    
    build_data.project_declare["spdlog"]()
    build_data.project_declare["SDL2"]()
    build_data.project_declare["ImGui"]()
    build_data.project_declare["DiligentToolsImGui"]("ThirdParty")
group ""

group "Projects"

project "Runtime"
    kind "StaticLib"
    language "C++"
    cppdialect "C++20"
    architecture "x64"
    staticruntime "On"
    
    targetdir(path.join(BUILD_BIN_DIR, outputdir))
    objdir(path.join(BUILD_OBJ_DIR, outputdir))
    
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
    }
    
    externalincludedirs
    {
        table.unpack(build_data.project_public_includes["spdlog"]()),
        
        table.unpack(build_data.project_public_includes["SDL2"]()),
        
        "ThirdParty/DiligentCore",
        table.unpack(build_data.project_public_includes["ImGui"]()),
        table.unpack(build_data.project_public_includes["DiligentCoreCommon"]()),
        table.unpack(build_data.project_public_includes["DiligentCoreGraphics"]()),
        table.unpack(build_data.project_public_includes["DiligentToolsImGui"]("ThirdParty/DiligentTools")),
    }
    runtimeincludedirs["spdlog"] = thirdpartydir .. "/%{includedirectory.spdlog}"
    
    forceincludes
    {
        "RuntimePCH.h"
    }
    
    -- Just here as a placeholder for a feature I intend to add at some point
    runtimelinks = {
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