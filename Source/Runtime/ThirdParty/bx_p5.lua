-- Folder that the repo sits in
local dep_root_path = "bx"
-- The ID to add the include path(s) to
local include_id = "bx"
-- Actual include directory path
local include_dir = path.join(dep_root_path, "include")
    
public_includes[include_id] = { include_dir }

function set_bx_compat()
	filter "action:vs*"
		includedirs { path.join(dep_root_path, "include/compat/msvc") }
	filter { "system:windows", "action:gmake" }
		includedirs { path.join(dep_root_path, "include/compat/mingw") }
	filter { "system:macosx" }
		includedirs { path.join(dep_root_path, "include/compat/osx") }
		buildoptions { "-x objective-c++" }
end

project "bx"
    location "bx"
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
        "__STDC_FORMAT_MACROS",
    }
    
    includedirs
    {
        path.join(dep_root_path, "3rdparty"),
        path.join(dep_root_path, "include")
    }
    
    files
    {
        path.join(dep_root_path, "include/bx/*.h"),
        path.join(dep_root_path, "include/bx/inline/*.inl"),
        path.join(dep_root_path, "src/*.cpp"),
    }
    excludes
    {
        path.join(dep_root_path, "src/amalgamated.cpp"),
        path.join(dep_root_path, "src/crtnone.cpp")
    }
    
    filter "action:vs*"
        defines "_CRT_SECURE_NO_WARNINGS"
        excludes
        {
            path.join(dep_root_path, "src/glcontext_glx.cpp"),
            path.join(dep_root_path, "src/glcontext_egl.cpp")
        }
        
    filter "action:vs*"
        defines "_CRT_SECURE_NO_WARNINGS"
        buildoptions { "/Zc:__cplusplus", "/Zc:preprocessor" }
        
    filter "configurations:Release"
        defines "BX_CONFIG_DEBUG=0"
    filter "configurations:Debug"
        defines "BX_CONFIG_DEBUG=1"
        
    set_bx_compat()