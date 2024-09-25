workspace "GammaRay"
    configurations { "Debug", "Release" }
    
    BUILD_BIN_DIR = "Build/Binaries"
    BUILD_OBJ_DIR = "Build/Intermediate"
    
    -- Table of includes by "ID" to be included into any main project
    public_includes = {}
    
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
