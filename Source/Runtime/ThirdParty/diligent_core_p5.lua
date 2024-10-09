include "DEGFX.lua"

DEGFX_InitRenderers(false, false, false)
DEGFX_IncludeProjects()

project "DiligentEngine"
    kind "StaticLib"
    staticruntime "On"
    language "C++"
    cppdialect "C++17"
    architecture "x64"
    DEGFX_Bind("DiligentCore")
-- 
-- 
-- local project_names = {
--     graphics = "DiligentGraphics"
-- }
-- 
-- local config = {
--     src_dir = nil
-- }
-- 
-- 
-- --==============================
-- -- Project Configurations
-- --==============================
-- 
-- build_data.project_configure[project_names.graphics] = function(src_dir)
--     config.src_dir = src_dir
-- end
-- 
-- 
-- --==============================
-- -- Public Includes
-- --==============================
-- 
-- build_data.project_public_includes[project_names.graphics] = function(base_dir)
--     return {
--     }
-- end
-- 
-- 
-- --==============================
-- -- Project Declarations
-- --==============================
-- 
-- build_data.project_declare[project_names.graphics] = function()
--     project "DiligentGraphics"
--         location(dep_root_path)
--         kind "StaticLib"
--         language "C++"
--         cppdialect "C++17"
--         architecture "x64"
--         
--         staticruntime "On"
--         runtime "Debug"
--         
--         targetdir (path.join(dep_root_path, BUILD_BIN_DIR, outputdir))
--         objdir (path.join(dep_root_path, BUILD_OBJ_DIR, outputdir))
--         
--         dependson { "DiligentCoreCommon", "DiligentPrimitives", "DiligentPlatformBasic", "DiligentPlatformWin" }
--         
--         flags {}
--         
--         defines {
--             "GL_SUPPORTED"
--         }
--         
--         includedirs {
--             path.join(config.src_dir, "Common/interface"),
--             path.join(config.src_dir, "Primitives/interface"),
--             path.join(config.src_dir, "Platforms/interface"),
--             path.join(config.src_dir, "Platforms/Basic/interface"),
--             
--             path.join(config.src_dir, "Graphics/GraphicsEngine/include"),
--             path.join(config.src_dir, "Graphics/GraphicsEngine/interface"),
--             path.join(config.src_dir, "Graphics/GraphicsAccessories/interface"),
--         }
--         
--         files {
--             path.join(config.src_dir, "Graphics/GraphicsEngine/src/**.cpp"),
--         }
--         excludes {}
--         
--         links { "DiligentCoreCommon", "DiligentPrimitives", "DiligentPlatformBasic", "DiligentPlatformWin" }
--             
--         filter "action:vs*"
--             defines "PLATFORM_WIN32"
--             
--         filter "system:windows"
--             files {
--             }
--             
--         filter "configurations:Release"
--         filter "configurations:Debug"
--         
--         DEGFX_AttachDefines()
-- end