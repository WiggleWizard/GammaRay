project "glad"
    location "glad"
    kind "StaticLib"
    staticruntime "on"
    language "C"

    targetdir ("glad/bin/" .. outputdir .. "/%{prj.name}")
    objdir ("glad/bin-obj/" .. outputdir .. "/%{prj.name}")

    files
    {
        "glad/include/glad/glad.h",
        "glad/include/KHR/khrplatform.h",
        "glad/src/glad.c"
    }

    includedirs
    {
        "glad/include"
    }

    filter "system:windows"
        systemversion "latest"

    filter "configurations:Debug"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        runtime "Release"
        optimize "on"