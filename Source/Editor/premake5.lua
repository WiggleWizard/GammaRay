project "Editor"
    kind "ConsoleApp"
    language "C++"
    cdialect "C17"
    cppdialect "C++latest"
    
    --cppmodules "true"
    buildstlmodules "On"
    architecture "x64"
    staticruntime "On"
    
    targetdir("Build/Binaries/" .. outputdir)
    objdir("Build/Intermediate/" .. outputdir)

    files
    {
        "Source/**.h",
        "Source/**.cpp",
        
        "Source/**.cpp2"
    }
    
    includedirs
    {
        rootdir .. "/Runtime/Source",
        rootdir .. "/Runtime/Thirdparty/cppfront"
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
    
    buildoptions
    {
        "/std:c++latest"
    }
    
    filter "files:Source/**.cpp2"
        buildmessage "Compiling %{file.relpath}"
        buildcommands {
            'cppfront %{file.relpath} -p -o %{file.reldirectory}/%{file.basename}.cpp'
        }
        buildoutputs {
            "%{file.reldirectory}/%{file.basename}.cpp"
        }
        
        compilebuildoutputs "On"
        
    filter "system:windows"

    filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"

    filter "configurations:Release"
        defines { "NDEBUG" }
        optimize "On"
