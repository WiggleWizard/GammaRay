-- Folder that the repo sits in
local dep_root_path = "DiligentTools"
-- The ID to add the include path(s) to
local include_id = "DiligentTools"
-- Actual include directory path
local include_dir = path.join(dep_root_path, "include")

local project_names = {
    imgui = "DiligentToolsImGui"
}

local config = {
    imgui_path = nil
}


--==============================
-- Project Configurations
--==============================

build_data.project_configure[project_names.imgui] = function(imgui_path)
    config.imgui_path = imgui_path
end


--==============================
-- Public Includes
--==============================

build_data.project_public_includes[project_names.imgui] = function()

end


--==============================
-- Project Declarations
--==============================

build_data.project_declare[project_names.imgui] = function(base_dir)
    dep_root_path = path.join(base_dir, dep_root_path)
    
    local imgui_path = config.imgui_path
    if (imgui_path == nil) then
        imgui_path = path.join(dep_root_path, "ThirdParty/imgui")
    end
    
    project "DiligentToolsImGui"
        location(dep_root_path)
        kind "StaticLib"
        staticruntime "on"
        language "C++"
        cppdialect "C++17"
        architecture "x64"
        
        targetdir (path.join(dep_root_path, BUILD_BIN_DIR, outputdir))
        objdir (path.join(dep_root_path, BUILD_OBJ_DIR, outputdir))
        
        flags {}
        
        defines {
        }
        
        includedirs {
            path.join(dep_root_path, "Imgui/interface"),
            imgui_path,
            
            path.join(dep_root_path, "ThirdParty/imGuIZMO.quat"),
            path.join(dep_root_path, "../DiligentCore/Common/interface"),
            path.join(dep_root_path, "../DiligentCore/Platforms/Win32/interface"),
            path.join(dep_root_path, "../DiligentCore/Platforms/Basic/interface"),
            path.join(dep_root_path, "../DiligentCore/Primitives/interface"),
            path.join(dep_root_path, "../DiligentCore/Platforms/interface"),
            path.join(dep_root_path, "../DiligentCore/Graphics/GraphicsEngine/interface"),
            path.join(dep_root_path, "../DiligentCore/Graphics/GraphicsAccessories/interface"),
            path.join(dep_root_path, "../DiligentCore/Graphics/GraphicsTools/interface"),
        }
        
        public_includes["DiligentToolsImGui"] = { path.join(dep_root_path, "Imgui/interface") }
        
        files {
            path.join(dep_root_path, "Imgui/src/ImGuiDiligentRenderer.cpp"),
            path.join(dep_root_path, "Imgui/src/ImGuiImplDiligent.cpp"),
        }
        excludes {}
            
        filter "action:vs*"
            defines "PLATFORM_WIN32"
            
        filter "system:windows"
            files {
                path.join(dep_root_path, "Imgui/src/ImGuiImplWin32.cpp"),
            }
            
        filter "configurations:Release"
        filter "configurations:Debug"
end