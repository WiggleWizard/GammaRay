-- Folder that the repo sits in
local dep_root_path = "bgfx"
-- The ID to add the include path(s) to
local include_id = "bgfx"
-- Actual include directory path
local include_dir = path.join(dep_root_path, "include")
    
public_includes[include_id] = { include_dir }

group "Dependencies"
    include "bimg_p5.lua"
    include "bx_p5.lua"

project "bgfx"
    location "bgfx"
    kind "StaticLib"
    staticruntime "on"
    language "C++"
    cppdialect "C++17"
    architecture "x64"
    
    targetdir (path.join(dep_root_path, BUILD_BIN_DIR, outputdir))
    objdir (path.join(dep_root_path, BUILD_OBJ_DIR, outputdir))
    
    flags {}
    
    defines
    {
        "__STDC_FORMAT_MACROS"
    }
    
    includedirs
    {
        path.join(dep_root_path, "include"),
        path.join(dep_root_path, "3rdparty"),
        path.join(dep_root_path, "3rdparty/dxsdk/include"),
        path.join(dep_root_path, "3rdparty/directx-headers/include/directx"),
        
        path.join(dep_root_path, "3rdparty/khronos"),
        
        table.unpack(public_includes["bx"]),
        table.unpack(public_includes["bimg"]),
    }
    
    files
    {
        path.join(dep_root_path, "include/bgfx/**.h"),
        path.join(dep_root_path, "src/**.cpp"),
        path.join(dep_root_path, "src/**.h"),
    }
    excludes
    {
        path.join(dep_root_path, "src/amalgamated.cpp"),
    }
    
    links
    {
        "bx"
    }
    
    filter "action:vs*"
        defines "_CRT_SECURE_NO_WARNINGS"
        excludes
        {
            path.join(dep_root_path, "src/glcontext_glx.cpp"),
            path.join(dep_root_path, "src/glcontext_egl.cpp")
        }
        buildoptions { "/Zc:__cplusplus", "/Zc:preprocessor" }
        
    filter "configurations:Release"
        defines "BX_CONFIG_DEBUG=0"
    filter "configurations:Debug"
        defines "BX_CONFIG_DEBUG=1"
        
    set_bx_compat()
    