-- Folder that the repo sits in
local dep_root_path = "bimg"
-- The ID to add the include path(s) to
local include_id = "bimg"
-- Actual include directory path
local include_dir = path.join(dep_root_path, "include")

public_includes[include_id] = { include_dir }

group "Dependencies"
    include "bx_p5.lua"

project "bimg"
    location "bimg"
    kind "StaticLib"
    staticruntime "on"
    language "C++"
    cppdialect "C++17"
    architecture "x64"
    
    targetdir (path.join(dep_root_path, BUILD_BIN_DIR, outputdir))
    objdir (path.join(dep_root_path, BUILD_OBJ_DIR, outputdir))
    
    flags {}
    
    defines {}
    
    includedirs
    {
        table.unpack(public_includes["bx"]),
        include_dir,
		path.join(dep_root_path, "3rdparty/astc-encoder/include"),
    }
    
    files
    {
		path.join(dep_root_path, "include/bimg/*.h"),
		path.join(dep_root_path, "src/image.cpp"),
		path.join(dep_root_path, "src/image_gnf.cpp"),
		path.join(dep_root_path, "src/*.h"),
		
		path.join(dep_root_path, "3rdparty/astc-encoder/source/**.cpp"),
		path.join(dep_root_path, "3rdparty/astc-encoder/source/**.h")
    }
    
    filter "action:vs*"
        defines "_CRT_SECURE_NO_WARNINGS"
        
    filter "action:vs*"
        defines "_CRT_SECURE_NO_WARNINGS"
        buildoptions { "/Zc:__cplusplus", "/Zc:preprocessor" }
        
    filter "configurations:Release"
        defines "BX_CONFIG_DEBUG=0"
    filter "configurations:Debug"
        defines "BX_CONFIG_DEBUG=1"
        
    set_bx_compat()