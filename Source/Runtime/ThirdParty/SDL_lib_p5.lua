local deprootpath = "SDL2"
local includedirectoryname = "sdl2"
local includedir = deprootpath .. "/include"

project "SDL2"
    location "SDL2"
    kind "SharedLib"
    architecture "x64"
    
    targetdir(deprootpath .. "/lib/x64")
    objdir(deprootpath .. "/Build/Intermediate/" .. outputdir)
    
    includedirectory[includedirectoryname] = includedir
        
    includedirs
    {
        includedir
    }
    
    links
    {
        deprootpath .. "lib/x64/SDL2.lib"
    }