workspace "shader2c"
    architecture "x64"

    configurations
    {
        "Debug",
        "Release"
    }

include "shader2c_p5.lua"
    filter "configurations:Debug"
        runtime "Debug"
        symbols "on"
        optimize "off"

    filter "configurations:Release"
        runtime "Release"
        optimize "on"