project "bin2c"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"

    targetdir ("bin")
    objdir ("bin-obj")

    configurations
    {
        "Debug",
        "Release"
    }
    
    files
    {
        "bin2c.cpp"
    }

    filter "configurations:Debug"
        runtime "Release"
        optimize "on"

    filter "configurations:Release"
        runtime "Release"
        optimize "on"
