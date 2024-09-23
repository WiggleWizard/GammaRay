project "Editor"
    kind "ConsoleApp"
    language "C++"
    cdialect "C17"
    cppdialect "C++20"
    architecture "x64"
    staticruntime "On"
    
    targetdir("Build/Binaries/" .. outputdir)
    objdir("Build/Intermediate/" .. outputdir)

    files
    {
        "Source/**.h",
        "Source/**.cpp",
    }
    
    includedirs
    {
        rootdir .. "/Runtime/Source",
    }
    
    externalincludedirs
    {
        runtimeincludedirs["spdlog"]
    }
    
    forceincludes
    {
        -- "EditorPCH.h"
    }
    
    -- pchheader "EditorPCH.h"
    -- pchsource "Source/EditorPCH.cpp"
    
    links
    {
        "Runtime",
    }
    
    defines
    {
    }
        
    filter "system:windows"

    filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"

    filter "configurations:Release"
        defines { "NDEBUG" }
        optimize "On"
