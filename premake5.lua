-- dofile("Tools/shadergen/premake5.lua")

workspace "GammaRay"
    architecture "x64"
    startproject "Sandbox"


    configurations
    {
        "Debug",
        "Release",
        "Dist"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"


-- Thirdparty vendor stuff
includeDirs = {}
includeDirs["GLFW"]   = "GammaRay/Thirdparty/glfw/include"
includeDirs["glad"]   = "GammaRay/Thirdparty/glad/include"
includeDirs["spdlog"] = "GammaRay/Thirdparty/spdlog/include"
includeDirs["tracy"]  = "GammaRay/Thirdparty/tracy"
includeDirs["imgui"]  = "GammaRay/Thirdparty/imgui"
includeDirs["glm"]    = "GammaRay/Thirdparty/glm"
includeDirs["entt"]    = "GammaRay/Thirdparty/entt/single_include"

include "GammaRay/Thirdparty/glfw_p5.lua"
include "GammaRay/Thirdparty/glad_p5.lua"
include "GammaRay/Thirdparty/imgui_p5.lua"


project "GammaRay"
    location "GammaRay"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"
    staticruntime "on"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-obj/" .. outputdir .. "/%{prj.name}")

    pchheader "grpch.h"
    pchsource "%{prj.name}/grpch.cpp"

    files
    {
        "%{prj.name}/grpch.h",
        "%{prj.name}/grpch.cpp",

        "%{prj.name}/Core/**.h",
        "%{prj.name}/Core/**.cpp",
        "%{prj.name}/Main/**.h",
        "%{prj.name}/Main/**.cpp",
        "%{prj.name}/Modules/**.h",
        "%{prj.name}/Modules/**.cpp",
        "%{prj.name}/Platform/**.h",
        "%{prj.name}/Platform/**.cpp",
        "%{prj.name}/Servers/**.h",
        "%{prj.name}/Servers/**.cpp",
        "%{prj.name}/Drivers/**.h",
        "%{prj.name}/Drivers/**.cpp",

        "%{prj.name}/Thirdparty/tracy/TracyClient.cpp"
    }

    includedirs
    {
        "%{prj.name}",
        "%{includeDirs.spdlog}",
        "%{includeDirs.tracy}",
        "%{includeDirs.GLFW}",
        "%{includeDirs.glad}",
        "%{includeDirs.imgui}",
        "%{includeDirs.glm}",
        "%{includeDirs.entt}",
    }

    links
    {
        "GLFW",
        "glad",
        "imgui",
        "opengl32.lib"
    }

    defines
    {
        "_CRT_SECURE_NO_WARNINGS"
    }

    -- Disable PCH for tracy
    filter "files:GammaRay/Thirdparty/tracy/TracyClient.cpp"
        flags { "NoPCH" }

    filter "system:windows"
        systemversion "latest"

        toolsdir = "$(ProjectDir)../Tools"
        shaderdir = "$(ProjectDir)Core/Renderer/Shaders"

        -- Disable edit and continue since Tracy doesn't like this
        editAndContinue "Off"

        -- Generate shaders from GLSL -> C headers
        prebuildcommands
        {
            toolsdir .. "/shader2c/bin/shader2c.exe --in=" .. shaderdir .. "/default.glsl --out=" .. shaderdir.. "/default.gen.h --class=Default --inherits=RendererShaderOpenGL --inheritshpath=Drivers/OpenGL/RendererShaderOpenGL.h"
        }

        defines
        {
            "GR_BUILD_DLL",
            "GR_PLATFORM_WINDOWS",

            -- So glad and GLFW play nice together
            "GLFW_INCLUDE_NONE",

            -- Disable "min" and "max" <Windows.h> macros so we can compile Tracy
            "NOMINMAX"
        }

    filter "configurations:Debug"
        runtime "Debug"
        symbols "on"

        defines
        {
            "GR_DEBUG",
            "GR_ENABLE_ASSERTS",

            -- Enable the below to profile memory in Tracy
            -- "GR_PROFILE_MEMORY"

            "DISABLE_FORCED_INLINE",

            -- Enable minimal on demand Tracy
            "TRACY_ENABLE",
            "TRACY_ON_DEMAND",
            "TRACY_NO_SYSTEM_TRACING"
        }

    filter "configurations:Release"
        defines "GR_RELEASE"
        runtime "Release"
        optimize "on"

    filter "configurations:Dist"
        defines "GR_DIST"
        runtime "Release"
        optimize "on"

project "Sandbox"
    location "Sandbox"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    staticruntime "on"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-obj/" .. outputdir .. "/%{prj.name}")

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",
    }

    includedirs
    {
        "GammaRay/Thirdparty/spdlog/include",
        "GammaRay",
        "GammaRay/Thirdparty",
        "%{includeDirs.glm}",
        "%{includeDirs.entt}",
    }

    links
    {
        "GammaRay"
    }

    filter "system:windows"
        staticruntime "on"
        systemversion "latest"

        defines
        {
            "GR_PLATFORM_WINDOWS"
        }

    filter "configurations:Debug"
        runtime "Debug"
        defines "GR_DEBUG"
        symbols "on"

    filter "configurations:Release"
        runtime "Release"
        defines "GR_RELEASE"
        optimize "on"

    filter "configurations:Dist"
        runtime "Release"
        defines "GR_DIST"
        optimize "on"

        

-- Tools