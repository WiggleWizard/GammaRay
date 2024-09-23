workspace "GammaRay"
    configurations { "Debug", "Release" }
    
    cppfrontincludedir = "Runtime/Thirdparty/cppfront"
    
    rootdir = _MAIN_SCRIPT_DIR;
    
    runtimedir = "Runtime"
    editordir = "Editor"
    
    outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"
    includedirectory = {}
    
    flags
    {
        "MultiProcessorCompile"
    }

group "Projects"
    include "Runtime/premake5.lua"
group "Projects"
    include "Editor/premake5.lua"
group ""
