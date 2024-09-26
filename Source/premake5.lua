BuildData = {}

function BuildData:new(o)
    o = o or {}   -- create object if user does not provide one
    setmetatable(o, self)
    self.__index = self
    
    self.project_public_includes = {}
    self.project_configure = {}
    self.project_declare = {}
    
    return o
end

build_data = BuildData:new();

workspace "GammaRay"
    configurations { "Debug", "Release" }
    
    BUILD_BIN_DIR = "Build/Binaries"
    BUILD_OBJ_DIR = "Build/Intermediate"
    
    -- Table of includes by "ID" to be included into any main project
    public_includes = {}
    
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
