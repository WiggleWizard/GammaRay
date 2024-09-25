--[[ 
Usage:
    
    // setup the paths and build options
    DEGFX_InitPaths(...)
    DEGFX_InitRenderers(...)
    
    // add the projects to build
    DEGFX_IncludeProjects()
    
    // In an active project that needs to reference DE-GFX
    DEGFX_Bind()
    
    example:
        project "MyProject"
            DEGFX_Bind()
]]--

local degfx_baseDir = "bin/"
local degfx_diligentSourceDir = "DiligentCore/"

local degfx_windows = true
local degfx_android = false

local degfx_useGL = true
local degfx_useD3D11 = false
local degfx_useD3D12 = false
local degfx_useVulkan = false

local degfx_engineD3D11 = ""
local degfx_engineD3DBase = ""
local degfx_engineD3D12 = ""
local degfx_engineGL = ""
local degfx_engineVulkan = ""

function DEGFX_InitPaths(deSrcDir, baseDir)
    degfx_diligentSourceDir = deSrcDir
    degfx_baseDir = baseDir
end

function DEGFX_InitRenderers(useD3D11, useD3D12, useVulkan)
    degfx_useD3D11 = useD3D11
    degfx_useD3D12 = useD3D12
    degfx_useGL = true
    degfx_useVulkan = useVulkan
    degfx_engineD3D11 = degfx_diligentSourceDir .. "Graphics/GraphicsEngineD3D11/interface"
    degfx_engineD3DBase = degfx_diligentSourceDir .. "Graphics/GraphicsEngineD3DBase/include"
    degfx_engineGL = degfx_diligentSourceDir .. "Graphics/GraphicsEngineOpenGL/include"
    degfx_engineVulkan = degfx_diligentSourceDir .. "Graphics/GraphicsEngineVulkan/interface"
end

function DEGFX_AttachDefines()
    if degfx_windows then
        defines { "PLATFORM_WIN32" }
    end
    if degfx_android then
        defines { "PLATFORM_ANDROID" }
    end
    
    if degfx_useD3D11 then
        defines { "D3D11_SUPPORTED" }
    end
    if degfx_useD3D12 then
        defines { "D3D11_SUPPORTED" }
    end
    if degfx_useVulkan then
        defines { "VULKAN_SUPPORTED" }
    end
end

function DEGFX_DeepDependency()
    dependson { "DiligentPrimitives", "DiligentCoreCommon", "DiligentPlatformBasic", "DiligentGraphicsAcc" }
    links { "DiligentPrimitives", "DiligentCoreCommon", "DiligentPlatformBasic", "DiligentGraphicsAcc" }
    includedirs {
        degfx_diligentSourceDir .. "Primitives/interface",
        degfx_diligentSourceDir .. "Common/interface",
        degfx_diligentSourceDir .. "Platforms/interface",
        degfx_diligentSourceDir .. "Platforms/Basic/interface",
        degfx_diligentSourceDir .. "Graphics/GraphicsEngine/interface",
        degfx_diligentSourceDir .. "Graphics/GraphicsEngine/include",
        degfx_diligentSourceDir .. "Graphics/GraphicsTools/include",
        degfx_diligentSourceDir .. "Graphics/GraphicsAccessories/interface",
    }
end

function DEGFX_AttachD3D11()
    defines { "D3D11_SUPPORTED" }
    links { "DiligentGraphicsD3D11", "DiligentGraphicsD3DBase" }
    dependson { "DiligentGraphicsD3D11", "DiligentGraphicsD3DBase" }
    includedirs { 
        degfx_diligentSourceDir .. "Graphics/GraphicsEngineD3D11/interface",
        degfx_diligentSourceDir .. "Graphics/GraphicsEngineD3DBase/include",
        degfx_diligentSourceDir .. "Graphics/GraphicsEngineD3DBase/interface",
        degfx_diligentSourceDir .. "Graphics/GraphicsEngineBase/include"
    }
end

function DEGFX_AttachD3D12()
    defines { "D3D12_SUPPORTED" }
    links { "DiligentGraphicsD3D12", "DiligentGraphicsD3DBase" }
    dependson { "DiligentGraphicsD3D12", "DiligentGraphicsD3DBase" }
    includedirs { 
        degfx_diligentSourceDir .. "Graphics/GraphicsEngineD3D12/interface",
        degfx_diligentSourceDir .. "Graphics/GraphicsEngineD3DBase/include",
        degfx_diligentSourceDir .. "Graphics/GraphicsEngineD3DBase/interface",
        degfx_diligentSourceDir .. "Graphics/GraphicsEngineBase/include"
    }
end

function DEGFX_AttachOpenGL()
    defines { "GL_SUPPORTED" }
    links { "DiligentGraphicsGL", "DiligentGraphicsD3DBase" }
    dependson { "DiligentGraphicsGL", "DiligentGraphicsD3DBase" }
    includedirs { 
        degfx_diligentSourceDir .. "Graphics/GraphicsEngineOpenGL/interface",
        degfx_diligentSourceDir .. "Graphics/GraphicsEngineBase/include"
    }
end

function DEGFX_AttachVulkan()
    defines { "VULKAN_SUPPORTED" }
    links { "DiligentGraphicsVulkan", "DiligentGraphicsD3DBase" }
    dependson { "DiligentGraphicsVulkan", "DiligentGraphicsD3DBase" }
    includedirs { 
        degfx_diligentSourceDir .. "Graphics/GraphicsEngineVulkan/interface",
        degfx_diligentSourceDir .. "Graphics/GraphicsEngineBase/include"
    }
end

function DEGFX_Bind(root_dir)
    if degfx_windows then
        defines { "PLATFORM_WIN32" }
        dependson { "DiligentPlatformWin" }
        links { "DiligentPlatformWin" }
        includedirs { root_dir .. "Graphics/Platforms/Win32/interface" }
    elseif degfx_android then
        defines { "PLATFORM_ANDROID" }
        dependson { "DiligentPlatformAndroid" }
        links { "DiligentPlatformAndroid" }
        includedirs { root_dir .. "Graphics/Platforms/Android/interface" }
    end
    
    DEGFX_AttachDefines()
    
    dependson {
        "DiligentPrimitives",
        "DiligentCoreCommon",
        "DiligentGraphicsTools",
        "DiligentGraphicsAcc",
        "DiligentPlatformBasic",
        "DiligentGraphics",
        "DiligentGraphicsOpenGL",
    }
    links {
        "DiligentPrimitives",
        "DiligentCoreCommon",
        "DiligentGraphicsTools",
        "DiligentGraphicsAcc",
        "DiligentPlatformBasic",
        "DiligentGraphics",
        "DiligentGraphicsOpenGL",
    } 
    
    includedirs {
        root_dir
    }
    
    if degfx_useD3D11 or degfx_useD3D12 then
        DEGFX_AttachD3D11()
    end
    if degfx_useD3D11 then
        DEGFX_AttachD3D12()
    end
    if degfx_useVulkan then
        DEGFX_AttachVulkan()
    end
end
        
function DEGFX_IncludeProjects()

    project "glew"
        architecture "x64"
        kind "StaticLib"
        language "C++"
        cppdialect "C++11"
        characterset "MBCS"
        location "Generated"
        
        files {
            degfx_diligentSourceDir .. "ThirdParty/glew/src/*.c",
        }
        
        includedirs {
            degfx_diligentSourceDir .. "ThirdParty/glew/include",
        }
        
        staticruntime "On"
        runtime "Debug"
        
        systemversion "latest"
        defines
        {
            "GLEW_STATIC",
            "_CRT_SECURE_NO_WARNINGS"
        }
        
    project "DiligentCoreCommon"
        architecture "x64"
        kind "StaticLib"
        language "C++"
        cppdialect "C++11"
        characterset "MBCS"
        location "Generated"
        
        staticruntime "On"
        runtime "Debug"
        
        targetdir (degfx_baseDir .. "DiligentCoreCommon/%{cfg.buildcfg}")
        dependson {  "DiligentPlatformBasic", "DiligentPrimitives" }
        links { "DiligentPlatformBasic", "DiligentPrimitives" }
        
        files {
            degfx_diligentSourceDir .. "Common/src/**.cpp",
        }
        removefiles {
            degfx_diligentSourceDir .. "Common/src/pch.cpp"
        }
        
        includedirs {
            degfx_diligentSourceDir .. "Common/include",
            degfx_diligentSourceDir .. "Common/interface",
            degfx_diligentSourceDir .. "Platforms/interface",
            degfx_diligentSourceDir .. "Platforms/Basic/interface",
            degfx_diligentSourceDir .. "Primitives/interface",
        }
        
        DEGFX_AttachDefines()
        
    project "DiligentPrimitives"
        architecture "x64"
        kind "StaticLib"
        language "C++"
        cppdialect "C++11"
        characterset "MBCS"
        location "Generated"
        staticruntime "On"
        runtime "Debug"
        
        targetdir (degfx_baseDir .. "DiligentPrimitives/%{cfg.buildcfg}")
        
        files {
            degfx_diligentSourceDir .. "Primitives/src/**.cpp"
        }
        includedirs {
            degfx_diligentSourceDir .. "Primitives/interface"
        }
        
    project "DiligentGraphics"
        architecture "x64"
        kind "StaticLib"
        language "C++"
        cppdialect "C++11"
        characterset "MBCS"
        location "Generated"
        staticruntime "On"
        runtime "Debug"
        
        targetdir (degfx_baseDir .. "DiligentGraphics/%{cfg.buildcfg}")
        dependson { "DiligentCoreCommon", "DiligentPrimitives", "DiligentPlatformBasic", "DiligentPlatformWin" }
        links { "DiligentCoreCommon", "DiligentPrimitives", "DiligentPlatformBasic", "DiligentPlatformWin" }
        
        files {
            degfx_diligentSourceDir .. "Graphics/GraphicsEngine/src/**.cpp"
        }
        includedirs {
            degfx_diligentSourceDir .. "Common/interface",
            degfx_diligentSourceDir .. "Primitives/interface",
            degfx_diligentSourceDir .. "Platforms/interface",
            degfx_diligentSourceDir .. "Platforms/Basic/interface",
            
            degfx_diligentSourceDir .. "Graphics/GraphicsEngine/include",
            degfx_diligentSourceDir .. "Graphics/GraphicsEngine/interface",        
            degfx_diligentSourceDir .. "Graphics/GraphicsAccessories/interface"
        }
        
        defines { "GL_SUPPORTED" }
        
        DEGFX_AttachDefines()
        
    project "DiligentGraphicsAcc"
        architecture "x64"
        kind "StaticLib"
        language "C++"
        cppdialect "C++11"
        characterset "MBCS"
        location "Generated"
        staticruntime "On"
        runtime "Debug"
        
        targetdir (degfx_baseDir .. "DiligentGraphicsAcc/%{cfg.buildcfg}")
        dependson { "DiligentCoreCommon", "DiligentPrimitives", "DiligentPlatformBasic", "DiligentPlatformWin" }
        links { "DiligentCoreCommon", "DiligentPrimitives", "DiligentPlatformBasic", "DiligentPlatformWin" }
        
        files { degfx_diligentSourceDir .. "Graphics/GraphicsAccessories/**.cpp" }
        
        includedirs { 
            degfx_diligentSourceDir .. "Graphics/GraphicsAccessories/interface",
            degfx_diligentSourceDir .. "Primitives/interface",
            degfx_diligentSourceDir .. "Platforms/Basic/interface",
            degfx_diligentSourceDir .. "Common/interface"
        }
        
        DEGFX_AttachDefines()

    project "DiligentGraphicsD3DBase"
        architecture "x64"
        kind "StaticLib"
        language "C++"
        cppdialect "C++11"
        characterset "MBCS"
        location "Generated"
        staticruntime "On"
        runtime "Debug"
        
        targetdir (degfx_baseDir .. "DiligentGraphicsD3DBase/%{cfg.buildcfg}")
        
        files {
            degfx_diligentSourceDir .. "Graphics/GraphicsEngineD3DBase/src/**.cpp"
        }
        
        includedirs {
            degfx_diligentSourceDir .. "Graphics/GraphicsEngineD3DBase/include",
            degfx_diligentSourceDir .. "Graphics/GraphicsEngineD3DBase/interface",
            degfx_diligentSourceDir .. "Graphics/ShaderTools/include",
            degfx_diligentSourceDir .. "ThirdParty/DirectXShaderCompiler",
            degfx_diligentSourceDir .. "Platforms/Win32/interface"
        }
        
        DEGFX_AttachDefines()
        DEGFX_DeepDependency()
        
    project "DiligentGraphicsTools"
        architecture "x64"
        kind "StaticLib"
        language "C++"
        cppdialect "C++11"
        characterset "MBCS"
        location "Generated"
        staticruntime "On"
        runtime "Debug"
        
        targetdir (degfx_baseDir .. "DiligentGraphicsTools/%{cfg.buildcfg}")
        dependson { "DiligentPrimitives", "DiligentCoreCommon", "DiligentPlatformBasic", "DiligentGraphicsAcc" }
        links { "DiligentPrimitives", "DiligentCoreCommon", "DiligentPlatformBasic", "DiligentGraphicsAcc" }
        
        files { degfx_diligentSourceDir .. "Graphics/GraphicsTools/src/**.cpp" }
        excludes { degfx_diligentSourceDir .. "Graphics/GraphicsTools/src/GraphicsUtilitiesVk.cpp" }
        excludes { degfx_diligentSourceDir .. "Graphics/GraphicsTools/src/GraphicsUtilitiesWebGPU.cpp" }
        excludes { degfx_diligentSourceDir .. "Graphics/GraphicsTools/src/GraphicsUtilitiesD3D*.cpp" }
        excludes { degfx_diligentSourceDir .. "Graphics/GraphicsTools/src/TextureUploaderWebGPU.cpp" }
        excludes { degfx_diligentSourceDir .. "Graphics/GraphicsTools/src/TextureUploaderD3D*.cpp" }
        includedirs {
            degfx_diligentSourceDir .. "Primitives/interface",
            degfx_diligentSourceDir .. "Common/interface",
            degfx_diligentSourceDir .. "Platforms/Basic/interface",
            degfx_diligentSourceDir .. "Platforms/interface",
            degfx_diligentSourceDir .. "Graphics/GraphicsEngine/interface",
            degfx_diligentSourceDir .. "Graphics/GraphicsEngine/include",
            degfx_diligentSourceDir .. "Graphics/GraphicsTools/include",
            degfx_diligentSourceDir .. "Graphics/GraphicsTools/interface",
            degfx_diligentSourceDir .. "Graphics/GraphicsAccessories/interface",
            degfx_diligentSourceDir .. "Graphics/ShaderTools/include",
            degfx_diligentSourceDir .. "ThirdParty/xxHash",
            degfx_diligentSourceDir .. "Graphics/Archiver/interface",
            degfx_diligentSourceDir .. "Graphics/Archiver/include",
        }
        
        defines { "GL_SUPPORTED" }
        
        if degfx_useD3D11 or degfx_useD3D12 then
            includedirs { degfx_engineD3DBase }
        end
        if degfx_useD3D11 == false then
            removefiles { degfx_diligentSourceDir .. "Graphics/GraphicsTools/src/*D3D11.cpp" }
        else
            includedirs { 
                degfx_diligentSourceDir .. "Graphics/GraphicsEngineD3D11/interface",
                degfx_diligentSourceDir .. "Graphics/GraphicsEngineD3D11/include" 
            }
        end
        
        if degfx_useD3D12 == false then
            removefiles { degfx_diligentSourceDir .. "Graphics/GraphicsTools/src/*D3D12.cpp" }
        else
            includedirs { 
                degfx_engineD3D12,
                degfx_diligentSourceDir .. "Graphics/GraphicsEngineD3D12/include" 
            }
        end
        
        if degfx_useGL == false then
            removefiles { degfx_diligentSourceDir .. "Graphics/GraphicsTools/src/*GL.cpp" }
        end
        
        DEGFX_AttachDefines()
        
    project "DiligentPlatformBasic"
        architecture "x64"
        kind "StaticLib"
        language "C++"
        cppdialect "C++11"
        characterset "MBCS"
        location "Generated"
        staticruntime "On"
        runtime "Debug"
        
        targetdir (degfx_baseDir .. "DiligentPlatformBasic/%{cfg.buildcfg}")
        dependson { "DiligentPrimitives" }
        links { "DiligentPrimitives" }
        
        files {
            degfx_diligentSourceDir .. "Platforms/Basic/src/**.cpp",
            degfx_diligentSourceDir .. "Platforms/Basic/interface/**.h"
        }
        
        removefiles { degfx_diligentSourceDir .. "Platforms/Basic/src/pch.cpp" }
        
        includedirs {
            degfx_diligentSourceDir .. "Platforms/Basic/interface",
            degfx_diligentSourceDir .. "Platforms/interface",
            degfx_diligentSourceDir .. "Primitives/interface"
        }
        
        defines { "PLATFORM_WIN32" }

    if degfx_windows then
        project "DiligentPlatformWin"
            architecture "x64"
            kind "StaticLib"
            language "C++"
            cppdialect "C++11"
            characterset "MBCS"
            location "Generated"
            staticruntime "On"
            runtime "Debug"
            
            targetdir (degfx_baseDir .. "DiligentPlatformWin/%{cfg.buildcfg}")
            dependson { "DiligentPlatformBasic", "DiligentPrimitives"  }
            links { "DiligentPlatformBasic", "DiligentPrimitives" }
            
            files { degfx_diligentSourceDir .. "Platforms/Win32/src/**.cpp" }
            
            removefiles { degfx_diligentSourceDir .. "Platforms/Win32/src/pch.cpp" }
            
            includedirs { 
                degfx_diligentSourceDir .. "Platforms/Win32/interface",
                degfx_diligentSourceDir .. "Platforms/interface",
                degfx_diligentSourceDir .. "Primitives/interface"
            }
            
            defines { "PLATFORM_WIN32" }
    end
    
    if degfx_useD3D11 then
        project "DiligentGraphicsD3D11"
            architecture "x64"
            kind "StaticLib"
            language "C++"
            cppdialect "C++11"
            characterset "MBCS"
            location "Generated"
            staticruntime "On"
            runtime "Debug"
            
            targetdir (degfx_baseDir .. "DiligentGraphicsD3D11/%{cfg.buildcfg}")
            dependson { "DiligentPrimitives", "DiligentCoreCommon", "DiligentPlatformBasic", "DiligentGraphicsAcc", "DiligentGraphics", "DiligentGraphicsD3DBase" }
            links { "DiligentPrimitives", "DiligentCoreCommon", "DiligentPlatformBasic", "DiligentGraphicsAcc", "DiligentGraphics", "DiligentGraphicsD3DBase" }
            
            files { degfx_diligentSourceDir .. "Graphics/GraphicsEngineD3D11/src/**.cpp" }
            includedirs {
                degfx_diligentSourceDir .. "Graphics/GraphicsEngineD3D11/include",
                degfx_diligentSourceDir .. "Graphics/GraphicsEngineD3D11/interface",
                degfx_diligentSourceDir .. "Graphics/GraphicsEngineD3DBase/include",
                degfx_diligentSourceDir .. "Graphics/GraphicsEngineD3DBase/interface",
            }
            
            DEGFX_AttachDefines()
            DEGFX_DeepDependency()
    end
    
    if degfx_useD3D12 then
        project "DiligentGraphicsD3D12"
            architecture "x64"
            kind "StaticLib"
            language "C++"
            cppdialect "C++11"
            characterset "MBCS"
            location "Generated"
            staticruntime "On"
            runtime "Debug"
            
            targetdir (degfx_baseDir .. "DiligentGraphicsD3D12/%{cfg.buildcfg}")
            dependson { "DiligentPrimitives", "DiligentCoreCommon", "DiligentPlatformBasic", "DiligentGraphicsAcc", "DiligentGraphics", "DiligentGraphicsD3DBase" }
            links { "DiligentPrimitives", "DiligentCoreCommon", "DiligentPlatformBasic", "DiligentGraphicsAcc", "DiligentGraphics", "DiligentGraphicsD3DBase" }
            
            files { degfx_diligentSourceDir .. "Graphics/GraphicsEngineD3D12/src/**.cpp" }
            includedirs {
                degfx_diligentSourceDir .. "Graphics/GraphicsEngineD3D12/include",
                degfx_diligentSourceDir .. "Graphics/GraphicsEngineD3D12/interface",
                degfx_diligentSourceDir .. "Graphics/GraphicsEngineD3DBase/include",
                degfx_diligentSourceDir .. "Graphics/GraphicsEngineD3DBase/interface",
            }
            
            DEGFX_AttachDefines()
            DEGFX_DeepDependency()
    end
    
    if degfx_useGL then
        project "DiligentGraphicsOpenGL"
            architecture "x64"
            kind "StaticLib"
            language "C++"
            cppdialect "C++11"
            characterset "MBCS"
            location "Generated"
            staticruntime "On"
            runtime "Debug"
            
            targetdir (degfx_baseDir .. "DiligentGraphicsOpenGL/%{cfg.buildcfg}")
            dependson { "DiligentPrimitives", "DiligentCoreCommon", "DiligentPlatformBasic", "DiligentGraphicsAcc", "DiligentGraphics", "DiligentGraphicsD3DBase" }
            links {
                "DiligentPrimitives",
                "DiligentCoreCommon",
                "DiligentPlatformBasic",
                "DiligentGraphicsAcc",
                "DiligentGraphics",
                "DiligentGraphicsD3DBase",
                "opengl32",
                "glu32"
            }
        
            defines { "GL_SUPPORTED" }
            
            files {
                path.join(degfx_diligentSourceDir, "Graphics/GraphicsEngineOpenGL/src/BufferGLImpl.cpp"),
                path.join(degfx_diligentSourceDir, "Graphics/GraphicsEngineOpenGL/src/BufferViewGLImpl.cpp"),
                path.join(degfx_diligentSourceDir, "Graphics/GraphicsEngineOpenGL/src/DeviceContextGLImpl.cpp"),
                path.join(degfx_diligentSourceDir, "Graphics/GraphicsEngineOpenGL/src/DeviceObjectArchiveGL.cpp"),
                path.join(degfx_diligentSourceDir, "Graphics/GraphicsEngineOpenGL/src/DearchiverGLImpl.cpp"),
                path.join(degfx_diligentSourceDir, "Graphics/GraphicsEngineOpenGL/src/EngineFactoryOpenGL.cpp"),
                path.join(degfx_diligentSourceDir, "Graphics/GraphicsEngineOpenGL/src/FBOCache.cpp"),
                path.join(degfx_diligentSourceDir, "Graphics/GraphicsEngineOpenGL/src/FenceGLImpl.cpp"),
                path.join(degfx_diligentSourceDir, "Graphics/GraphicsEngineOpenGL/src/FramebufferGLImpl.cpp"),
                path.join(degfx_diligentSourceDir, "Graphics/GraphicsEngineOpenGL/src/GLContextState.cpp"),
                path.join(degfx_diligentSourceDir, "Graphics/GraphicsEngineOpenGL/src/GLObjectWrapper.cpp"),
                path.join(degfx_diligentSourceDir, "Graphics/GraphicsEngineOpenGL/src/GLProgram.cpp"),
                path.join(degfx_diligentSourceDir, "Graphics/GraphicsEngineOpenGL/src/GLProgramCache.cpp"),
                path.join(degfx_diligentSourceDir, "Graphics/GraphicsEngineOpenGL/src/GLTypeConversions.cpp"),
                path.join(degfx_diligentSourceDir, "Graphics/GraphicsEngineOpenGL/src/PipelineResourceSignatureGLImpl.cpp"),
                path.join(degfx_diligentSourceDir, "Graphics/GraphicsEngineOpenGL/src/PipelineStateGLImpl.cpp"),
                path.join(degfx_diligentSourceDir, "Graphics/GraphicsEngineOpenGL/src/QueryGLImpl.cpp"),
                path.join(degfx_diligentSourceDir, "Graphics/GraphicsEngineOpenGL/src/RenderDeviceGLImpl.cpp"),
                path.join(degfx_diligentSourceDir, "Graphics/GraphicsEngineOpenGL/src/RenderPassGLImpl.cpp"),
                path.join(degfx_diligentSourceDir, "Graphics/GraphicsEngineOpenGL/src/SamplerGLImpl.cpp"),
                path.join(degfx_diligentSourceDir, "Graphics/GraphicsEngineOpenGL/src/ShaderGLImpl.cpp"),
                path.join(degfx_diligentSourceDir, "Graphics/GraphicsEngineOpenGL/src/ShaderResourceBindingGLImpl.cpp"),
                path.join(degfx_diligentSourceDir, "Graphics/GraphicsEngineOpenGL/src/ShaderResourceCacheGL.cpp"),
                path.join(degfx_diligentSourceDir, "Graphics/GraphicsEngineOpenGL/src/ShaderResourcesGL.cpp"),
                path.join(degfx_diligentSourceDir, "Graphics/GraphicsEngineOpenGL/src/ShaderVariableManagerGL.cpp"),
                path.join(degfx_diligentSourceDir, "Graphics/GraphicsEngineOpenGL/src/Texture1D_GL.cpp"),
                path.join(degfx_diligentSourceDir, "Graphics/GraphicsEngineOpenGL/src/Texture1DArray_GL.cpp"),
                path.join(degfx_diligentSourceDir, "Graphics/GraphicsEngineOpenGL/src/Texture2D_GL.cpp"),
                path.join(degfx_diligentSourceDir, "Graphics/GraphicsEngineOpenGL/src/Texture2DArray_GL.cpp"),
                path.join(degfx_diligentSourceDir, "Graphics/GraphicsEngineOpenGL/src/Texture3D_GL.cpp"),
                path.join(degfx_diligentSourceDir, "Graphics/GraphicsEngineOpenGL/src/TextureBaseGL.cpp"),
                path.join(degfx_diligentSourceDir, "Graphics/GraphicsEngineOpenGL/src/TextureCube_GL.cpp"),
                path.join(degfx_diligentSourceDir, "Graphics/GraphicsEngineOpenGL/src/TextureCubeArray_GL.cpp"),
                path.join(degfx_diligentSourceDir, "Graphics/GraphicsEngineOpenGL/src/TextureViewGLImpl.cpp"),
                path.join(degfx_diligentSourceDir, "Graphics/GraphicsEngineOpenGL/src/VAOCache.cpp"),
                
                path.join(degfx_diligentSourceDir, "Graphics/HLSL2GLSLConverterLib/src/**.cpp"),
                
                path.join(degfx_diligentSourceDir, "Graphics/ShaderTools/src/DXBCUtils.cpp"),
                path.join(degfx_diligentSourceDir, "Graphics/ShaderTools/src/DXCompiler.cpp"),
                path.join(degfx_diligentSourceDir, "Graphics/ShaderTools/src/DXCompilerLibrary.cpp"),
                path.join(degfx_diligentSourceDir, "Graphics/ShaderTools/src/DXCompilerLibraryWin32.cpp"),
                path.join(degfx_diligentSourceDir, "Graphics/ShaderTools/src/DXILUtilsStub.cpp"),
                path.join(degfx_diligentSourceDir, "Graphics/ShaderTools/src/GLSLangUtils.cpp"),
                path.join(degfx_diligentSourceDir, "Graphics/ShaderTools/src/GLSLParsingTools.cpp"),
                path.join(degfx_diligentSourceDir, "Graphics/ShaderTools/src/GLSLUtils.cpp"),
                path.join(degfx_diligentSourceDir, "Graphics/ShaderTools/src/HLSLParsingTools.cpp"),
                path.join(degfx_diligentSourceDir, "Graphics/ShaderTools/src/HLSLTokenizer.cpp"),
                path.join(degfx_diligentSourceDir, "Graphics/ShaderTools/src/HLSLUtils.cpp"),
                path.join(degfx_diligentSourceDir, "Graphics/ShaderTools/src/ShaderToolsCommon.cpp"),
                path.join(degfx_diligentSourceDir, "Graphics/ShaderTools/src/SPIRVShaderResources.cpp"),
                path.join(degfx_diligentSourceDir, "Graphics/ShaderTools/src/SPIRVTools.cpp"),
                path.join(degfx_diligentSourceDir, "Graphics/ShaderTools/src/SPIRVUtils.cpp"),
                path.join(degfx_diligentSourceDir, "Graphics/ShaderTools/include/SPIRVShaderResources.hpp"),
            }
            includedirs {
                degfx_diligentSourceDir .. "Graphics/GraphicsEngineOpenGL/include",
                degfx_diligentSourceDir .. "Graphics/GraphicsEngineOpenGL/interface",
                degfx_diligentSourceDir .. "Graphics/GraphicsEngineD3DBase/include",
                degfx_diligentSourceDir .. "Graphics/GraphicsEngineD3DBase/interface",
                degfx_diligentSourceDir .. "Graphics/ShaderTools/include",
                degfx_diligentSourceDir .. "Graphics/HLSL2GLSLConverterLib/include",
                degfx_diligentSourceDir .. "Graphics/HLSL2GLSLConverterLib/interface",
                degfx_diligentSourceDir .. "Platforms/Win32/interface",
                degfx_diligentSourceDir .. "ThirdParty/glew/include",
                
                degfx_diligentSourceDir .. "ThirdParty/SPIRV-cross",
                degfx_diligentSourceDir .. "ThirdParty/SPIRV-tools/include",
                degfx_diligentSourceDir .. "ThirdParty/glslang",
                degfx_diligentSourceDir .. "ThirdParty/DirectXShaderCompiler",
                
                degfx_diligentSourceDir .. "../DiligentCoreGen",
            }
            
            filter "system:windows"
                defines {
                    "PLATFORM_WIN32"
                }

                includedirs {
                    path.join(degfx_diligentSourceDir, "Platforms/Win32/interface")
                }

                files {
                    path.join(degfx_diligentSourceDir, "Platforms/Win32/src/**.cpp"),

                    path.join(degfx_diligentSourceDir, "Graphics/GraphicsEngineOpenGL/src/GLContextWindows.cpp"),
                    path.join(degfx_diligentSourceDir, "Graphics/GraphicsEngineOpenGL/src/SwapChainGLImpl.cpp"),
                }
            
            DEGFX_AttachDefines()
            DEGFX_DeepDependency()
    end
end