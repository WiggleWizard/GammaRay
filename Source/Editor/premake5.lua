local includes = build_data.project_public_includes["spdlog"]()
for k, v in pairs(includes) do
    includes[k] = path.join("../Runtime", includes[k])
end

project "Editor"
    kind "ConsoleApp"
    language "C++"
    cdialect "C17"
    cppdialect "C++20"
    architecture "x64"
    staticruntime "On"
    
    targetdir("Build/Binaries/" .. outputdir)
    objdir("Build/Intermediate/" .. outputdir)

    files {
        "Source/**.h",
        "Source/**.cpp",
    }
    
    includedirs {
        rootdir .. "/Runtime/Source",
    }
    
    externalincludedirs {
        table.unpack(includes)
    }
    
    forceincludes {
        -- "EditorPCH.h"
    }
    
    -- pchheader "EditorPCH.h"
    -- pchsource "Source/EditorPCH.cpp"
    
    links {
        "Runtime",
    }
    
    defines {
    }
        
    filter "system:windows"

    filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"

    filter "configurations:Release"
        defines { "NDEBUG" }
        optimize "On"
