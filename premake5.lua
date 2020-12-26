workspace "GammaRay"
    architecture "x64"

    configurations
    {
        "Debug",
        "Release",
        "Dist"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"


project "GammaRay"
    location "GammaRay"
    kind "SharedLib"
    language "C++"

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

        "%{prj.name}/Thirdparty/tracy/TracyClient.cpp"
    }

    includedirs
    {
        "%{prj.name}",
        "%{prj.name}/Thirdparty/spdlog/include",
        "%{prj.name}/Thirdparty/tracy",
    }

    -- Disable PCH for tracy
    filter "files:GammaRay/Thirdparty/tracy/TracyClient.cpp"
        flags { "NoPCH" }

    filter "system:windows"
        cppdialect "C++17"
        staticruntime "On"
        systemversion "latest"
        -- Disable edit and continue since Tracy doesn't like this
        editAndContinue "Off"

        defines
        {
            "GR_BUILD_DLL",
            "GR_PLATFORM_WINDOWS",
            "NOMINMAX"
        }

        postbuildcommands
        {
            ("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
        }

    filter "configurations:Debug"
        defines
        {
            "GR_DEBUG",
            "TRACY_ENABLE",
            "TRACY_ON_DEMAND",
            "TRACY_NO_SYSTEM_TRACING"
        }
        symbols "On"

    filter "configurations:Release"
        defines "GR_RELEASE"
        optimize "On"

    filter "configurations:Dist"
        defines "GR_DIST"
        optimize "On"

project "Sandbox"
    location "Sandbox"
    kind "ConsoleApp"
    language "C++"

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
        "GammaRay"
    }

    links
    {
        "GammaRay"
    }

    filter "system:windows"
        cppdialect "C++17"
        staticruntime "On"
        systemversion "latest"

        defines
        {
            "GR_PLATFORM_WINDOWS"
        }

    filter "configurations:Debug"
        defines "GR_DEBUG"
        symbols "On"

    filter "configurations:Release"
        defines "GR_RELEASE"
        optimize "On"

    filter "configurations:Dist"
        defines "GR_DIST"
        optimize "On"
