local project_name = "spdlog"

local config = {
    lib_dir = "",
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
    
    project "spdlog"
        location(lib_dir)
        kind "StaticLib"
        staticruntime "on"
        language "C++"
        architecture "x64"
        
        targetdir (path.join(lib_dir, BUILD_BIN_DIR, outputdir))
        objdir (path.join(lib_dir, BUILD_OBJ_DIR, outputdir))
        
        flags {}
        
        defines
        {
            "SPDLOG_COMPILED_LIB",
            "WIN32_LEAN_AND_MEAN"
        }
        
        includedirs
        {
            path.join(lib_dir, "include")
        }
        
        files
        {
            path.join(lib_dir, "src/**.cpp")
        }
end
    