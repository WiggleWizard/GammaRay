local project_name = "SDL2"

local config = {
    lib_dir = "SDL2"
}

--==============================
-- Project Configurations
--==============================

build_data.project_configure[project_name] = function(lib_dir)
    config.lib_dir = lib_dir
end


--==============================
-- Public Includes
--==============================

build_data.project_public_includes[project_name] = function()
    return {
        path.join(config.lib_dir, "include")
    }
end


--==============================
-- Project Declarations
--==============================

build_data.project_declare[project_name] = function()
    local lib_dir = config.lib_dir
    
    project "SDL2"
        location(lib_dir)
        kind "SharedLib"
        architecture "x64"
        
        targetdir(path.join(lib_dir, "lib/x64"))
        objdir(path.join(lib_dir, BUILD_OBJ_DIR, outputdir))
            
        includedirs {
            "include"
        }
        
        libdirs {
            --path.join(lib_dir, "/lib/x64"),
        }
        
        links {
            --path.join(lib_dir, "/lib/x64/SDL2.lib"),
        }
end

