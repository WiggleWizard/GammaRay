local project_name = "ImGui"


--==============================
-- Project Configurations
--==============================

build_data.project_configure[project_name] = function(lib_dir)
    -- No Configuration Needed
end


--==============================
-- Public Includes
--==============================

build_data.project_public_includes[project_name] = function(lib_dir)
    return {
        lib_dir
    }
end


--==============================
-- Project Declarations
--==============================

build_data.project_declare[project_name] = function(lib_dir)
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
        }
        
        files {
            path.join(lib_dir, "*.cpp")
        }
        excludes {}
            
        filter "action:vs*"
            
        filter "system:windows"
            files {
                path.join(lib_dir, "backends/imgui_impl_win32.cpp")
            }
            
        filter "configurations:Release"
        filter "configurations:Debug"
end