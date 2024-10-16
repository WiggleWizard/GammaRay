local project_name = "entt"

local config = {
    lib_dir = "",
}


--==============================
-- Project Configurations
--==============================

local config_fn = function(lib_dir)
    config.lib_dir = lib_dir
end
dep_set_config_fn(project_name, config_fn)


--==============================
-- Public Includes
--==============================

local public_includes_fn = function()
    return {
        path.join(config.lib_dir, "src")
    }
end
dep_set_public_includes_fn(project_name, public_includes_fn)


--==============================
-- Project Declarations
--==============================

local decl_fn = function()
    local lib_dir = config.lib_dir

    project "entt"
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
            path.join(config.lib_dir, "src")
        }
        
        files {
        }
        excludes {}
            
        filter "action:vs*"
        filter "system:windows"
        filter "configurations:Release"
        filter "configurations:Debug"
end
dep_declare_project_fn(project_name, decl_fn)