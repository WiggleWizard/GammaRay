
local external_includes = {
    "spdlog", "DiligentCoreCommon", "DiligentCoreGraphics", "entt"
}
local includes = {}

for _, public_include_name in pairs(external_includes) do
    for k, v in pairs(build_data.project_public_includes[public_include_name]()) do
        table.insert(includes, path.join("../Runtime", v))
    end
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
        table.unpack(includes),
    }
    
    forceincludes {
        "EditorPCH.h"
    }
    
    pchheader "EditorPCH.h"
    pchsource "Source/EditorPCH.cpp"
    
    links {
        "Runtime",
    }
    
    defines {
    }
        
    filter "system:windows"
        defines { "PLATFORM_WIN32" }

    filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"

    filter "configurations:Release"
        defines { "NDEBUG" }
        optimize "On"
