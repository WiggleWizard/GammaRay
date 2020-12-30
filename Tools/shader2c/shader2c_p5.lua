project "shader2c"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"

    targetdir ("bin")
    objdir ("bin-obj")

    files
    {
        "shader2c.cpp"
    }

    runtime "Release"
    optimize "on"
