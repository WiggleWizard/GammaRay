local project_name = "ImGui"

local config = {
    lib_dir = "",
    sdl_include_dir = ""
}


--==============================
-- Project Configurations
--==============================

build_data.project_configure[project_name] = function(lib_dir, sdl_include_dir)
    config.lib_dir = lib_dir
    config.sdl_include_dir = sdl_include_dir
end


--==============================
-- Public Includes
--==============================

build_data.project_public_includes[project_name] = function()
    return {
        config.lib_dir
    }
end


--==============================
-- Project Declarations
--==============================

build_data.project_declare[project_name] = function()
    local lib_dir = config.lib_dir

    project "ImGui"
        location(lib_dir)
        kind "StaticLib"
        staticruntime "on"
        language "C++"
        cppdialect "C++17"
        architecture "x64"
        
        targetdir (path.join(lib_dir, BUILD_BIN_DIR, outputdir))
        objdir (path.join(lib_dir, BUILD_OBJ_DIR, outputdir))
        
        flags {}
        
        defines {
        }
        
        includedirs {
            lib_dir,
            config.sdl_include_dir,
        }
        
        files {
            path.join(lib_dir, "*.cpp")
        }
        excludes {}
            
        filter "action:vs*"
            
        filter "system:windows"
            files {
                path.join(lib_dir, "backends/imgui_impl_win32.cpp"),
                path.join(lib_dir, "backends/imgui_impl_sdl2.cpp")
            }
            
        filter "configurations:Release"
        filter "configurations:Debug"
end