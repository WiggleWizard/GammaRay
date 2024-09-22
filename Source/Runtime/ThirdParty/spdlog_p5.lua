local deprootpath = "spdlog"
local includedirectoryname = "spdlog"
local includedir = deprootpath .. "/include"

project "spdlog"
    location "spdlog"
    kind "StaticLib"
    staticruntime "on"
    language "C++"
    architecture "x64"
    
    targetdir (deprootpath .. "/Build/Binaries/" .. outputdir)
    objdir (deprootpath .. "/Build/Intermediate/" .. outputdir)
    
    flags {}
    
    defines
    {
        "SPDLOG_COMPILED_LIB",
        "WIN32_LEAN_AND_MEAN"
    }
    
    includedirectory[includedirectoryname] = includedir
    
    includedirs
    {
        includedir
    }
    
    files
    {
        deprootpath .. "/src/*.cpp"
    }
    
    