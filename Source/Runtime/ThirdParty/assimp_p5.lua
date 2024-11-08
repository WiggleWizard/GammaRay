local project_name = "assimp"

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
        path.join(config.lib_dir, "include"),
        path.join(config.lib_dir, "../build"),
    }
end
dep_set_public_includes_fn(project_name, public_includes_fn)


--==============================
-- Project Declarations
--==============================

local decl_fn = function()
    local lib_dir = config.lib_dir

    project "assimp"
        location(lib_dir)
        kind "StaticLib"
        staticruntime "on"
        language "C++"
        cppdialect "C++17"
        architecture "x64"
        
        targetdir (path.join(lib_dir, BUILD_BIN_DIR, outputdir))
        objdir (path.join(lib_dir, BUILD_OBJ_DIR, outputdir))
        
        flags {}
        
        -- Importers
        	defines {
        		'ASSIMP_BUILD_NO_EXPORT',
        		'ASSIMP_BUILD_NO_3D_IMPORTER',
        		'ASSIMP_BUILD_NO_3DS_IMPORTER',
        		'ASSIMP_BUILD_NO_3MF_IMPORTER',
        		'ASSIMP_BUILD_NO_AC_IMPORTER',
        		'ASSIMP_BUILD_NO_AMF_IMPORTER',
        		'ASSIMP_BUILD_NO_ASE_IMPORTER',
        		'ASSIMP_BUILD_NO_ASSBIN_IMPORTER',
        		'ASSIMP_BUILD_NO_B3D_IMPORTER',
        		'ASSIMP_BUILD_NO_BLEND_IMPORTER',
        		'ASSIMP_BUILD_NO_BVH_IMPORTER',
        		'ASSIMP_BUILD_NO_C4D_IMPORTER',
        		'ASSIMP_BUILD_NO_COB_IMPORTER',
        		-- 'ASSIMP_BUILD_NO_COLLADA_IMPORTER',
        		'ASSIMP_BUILD_NO_CSM_IMPORTER',
        		'ASSIMP_BUILD_NO_DXF_IMPORTER',
        		-- 'ASSIMP_BUILD_NO_FBX_IMPORTER',
        		-- 'ASSIMP_BUILD_NO_GLTF_IMPORTER',
        		'ASSIMP_BUILD_NO_HMP_IMPORTER',
        		'ASSIMP_BUILD_NO_IFC_IMPORTER',
        		'ASSIMP_BUILD_NO_IRR_IMPORTER',
        		'ASSIMP_BUILD_NO_IRRMESH_IMPORTER',
        		'ASSIMP_BUILD_NO_LWO_IMPORTER',
        		'ASSIMP_BUILD_NO_LWS_IMPORTER',
        		'ASSIMP_BUILD_NO_M3D_IMPORTER',
        		--'ASSIMP_BUILD_NO_MD2_IMPORTER',
        		--'ASSIMP_BUILD_NO_MD3_IMPORTER',
        		'ASSIMP_BUILD_NO_MD5_IMPORTER',
        		'ASSIMP_BUILD_NO_MDC_IMPORTER',
        		--'ASSIMP_BUILD_NO_MDL_IMPORTER',
        		'ASSIMP_BUILD_NO_MMD_IMPORTER',
        		'ASSIMP_BUILD_NO_MS3D_IMPORTER',
        		'ASSIMP_BUILD_NO_NDO_IMPORTER',
        		'ASSIMP_BUILD_NO_NFF_IMPORTER',
        		-- 'ASSIMP_BUILD_NO_OBJ_IMPORTER',
        		'ASSIMP_BUILD_NO_OFF_IMPORTER',
        		'ASSIMP_BUILD_NO_OGRE_IMPORTER',
        		'ASSIMP_BUILD_NO_OPENGEX_IMPORTER',
        		'ASSIMP_BUILD_NO_PLY_IMPORTER',
        		'ASSIMP_BUILD_NO_Q3BSP_IMPORTER',
        		'ASSIMP_BUILD_NO_Q3D_IMPORTER',
        		'ASSIMP_BUILD_NO_RAW_IMPORTER',
        		'ASSIMP_BUILD_NO_SIB_IMPORTER',
        		'ASSIMP_BUILD_NO_SMD_IMPORTER',
        		'ASSIMP_BUILD_NO_STEP_IMPORTER',
        		'ASSIMP_BUILD_NO_STL_IMPORTER',
        		'ASSIMP_BUILD_NO_TERRAGEN_IMPORTER',
        		'ASSIMP_BUILD_NO_X_IMPORTER',
        		'ASSIMP_BUILD_NO_X3D_IMPORTER',
        		'ASSIMP_BUILD_NO_XGL_IMPORTER',
        		'ASSIMP_BUILD_NO_IQM_IMPORTER',
        		'ASSIMP_BUILD_NO_USD_IMPORTER',
        	}
        	-- Exporters
        	defines {
        		'ASSIMP_BUILD_NO_COLLADA_EXPORTER',
        		'ASSIMP_BUILD_NO_X_EXPORTER',
        		'ASSIMP_BUILD_NO_STEP_EXPORTER',
        		'ASSIMP_BUILD_NO_OBJ_EXPORTER',
        		'ASSIMP_BUILD_NO_STL_EXPORTER',
        		'ASSIMP_BUILD_NO_PLY_EXPORTER',
        		'ASSIMP_BUILD_NO_3DS_EXPORTER',
        		'ASSIMP_BUILD_NO_GLTF_EXPORTER',
        		-- 'ASSIMP_BUILD_NO_ASSBIN_EXPORTER',
        		'ASSIMP_BUILD_NO_ASSXML_EXPORTER',
        		'ASSIMP_BUILD_NO_X3D_EXPORTER',
        		'ASSIMP_BUILD_NO_FBX_EXPORTER',
        		'ASSIMP_BUILD_NO_M3D_EXPORTER',
        		'ASSIMP_BUILD_NO_3MF_EXPORTER',
        		'ASSIMP_BUILD_NO_ASSJSON_EXPORTER',
        		'ASSIMP_BUILD_NO_USD_EXPORTER',
        	}
        
        includedirs {
            path.join(config.lib_dir, "..", "build"),
            path.join(config.lib_dir, "..", "build/assimp"),
            
            path.join(config.lib_dir, "include"),
            path.join(config.lib_dir, "contrib/irrXML"),
            path.join(config.lib_dir, "contrib/unzip"),
            path.join(config.lib_dir, "contrib/zlib"),
            path.join(config.lib_dir, "contrib/rapidjson/include"),
            path.join(config.lib_dir, "contrib/utf8cpp/source"),
            path.join(config.lib_dir, "contrib/pugixml/src"),
            path.join(config.lib_dir, "code")
        }
        
        files {
--             path.join(config.lib_dir, "include/**"),
--             path.join(config.lib_dir, "code/Common/**"),
--             path.join(config.lib_dir, "code/AssetLib/Obj/**"),
--             path.join(config.lib_dir, "code/PostProcessing/**"),
            
            path.join(config.lib_dir, "contrib/unzip/**"),
            path.join(config.lib_dir, "contrib/irrXML/**"),
            path.join(config.lib_dir, "contrib/zlib/*"),
            path.join(config.lib_dir, "contrib/pugixml/src/**"),
            path.join(config.lib_dir, "code/Common/**"),
            path.join(config.lib_dir, "code/PostProcessing/**"),
            path.join(config.lib_dir, "code/Material/**"),
            path.join(config.lib_dir, "code/CApi/**"),
            path.join(config.lib_dir, "code/AssetLib/Collada/**"),
            path.join(config.lib_dir, "code/AssetLib/Obj/**"),
            path.join(config.lib_dir, "code/AssetLib/FBX/**"),
            path.join(config.lib_dir, "code/glTF2/**"),
            path.join(config.lib_dir, "code/AssetLib/glTF/**"),
            path.join(config.lib_dir, "code/AssetLib/glTF2/**"),
            path.join(config.lib_dir, "code/AssetLib/MDL/**"),
            path.join(config.lib_dir, "code/AssetLib/MD2/**"),
            path.join(config.lib_dir, "code/AssetLib/MD3/**"),
            path.join(config.lib_dir, "code/Assbin/**"),
            path.join(config.lib_dir, "code/Geometry/**"),
        }
        excludes {}
            
        filter "system:windows"
            systemversion "latest"
            
        filter  "configurations:Debug"
            runtime "Debug"
            symbols "on"
            
        filter  "configurations:Release"
            runtime "Release"
            optimize "on"
end
dep_declare_project_fn(project_name, decl_fn)