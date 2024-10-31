#include "Renderer3D.h"

#include "Engine/World.h"
#include "ImGui/ImGuiImplSDLDiligent.h"
#include "Windowing/Window.h"
#include "Rendering/Viewport.h"
#include "Rendering/WindowViewport.h"
#include "Scene/Components/CameraComponent.h"
#include "Scene/Components/TransformComponent.h"
#include "Scene/Components/StaticMeshComponent.h"
#include "Scene3D.h"
#include "PSOs/PSOGrid.h"
#include "Scene/Components/MaterialComponent.h"
#include "Scene/Components/SimpleMeshComponent.h"

#include <GraphicsTypes.h>
#include <ImGuiImplDiligent.hpp>
#include <entt/entt.hpp>
#include <BasicMath.hpp>

#include <SwapChain.h>
#include <Graphics/GraphicsEngineOpenGL/interface/EngineFactoryOpenGL.h>
#include <Graphics/GraphicsTools/interface/MapHelper.hpp>

DEFINE_LOGGER_STATIC(LogRenderer3D, LogVerbosity::Type::Warning);
DEFINE_LOGGER_STATIC(LogDiligent, LogVerbosity::Type::Warning);

static const char* VSSource = R"(
// Attributes
layout(location = 0) in vec3 ATTRIB0_Position;
layout(location = 1) in vec3 ATTRIB1_Normal;
layout(location = 2) in vec2 ATTRIB2_UV;
layout(location = 3) in vec4 ATTRIB3_Color;

// Constant buffer
layout(std140, binding = 0) uniform VSConstants
{
    mat4 g_WorldViewProj;
    mat4 g_World;
};

// Outputs to fragment shader
layout(location = 0) out vec3 out_WorldPos;
layout(location = 1) out vec3 out_Normal;
layout(location = 2) out vec2 out_UV;
layout(location = 3) out vec4 out_Color;

void main()
{
    // Transform world position
    vec4 worldPos = g_World * vec4(ATTRIB0_Position, 1.0);
    out_WorldPos = worldPos.xyz;
    
    // Transform to clip space
    gl_Position = g_WorldViewProj * vec4(ATTRIB0_Position, 1.0);
    
    // Transform normal to world space
    out_Normal = mat3(g_World) * ATTRIB1_Normal;
    
    // Pass through texture coordinates
    out_UV = ATTRIB2_UV;

    out_Color = ATTRIB3_Color;
}
)";

// Pixel shader simply outputs interpolated vertex color
static const char* PSSource = R"(
// Inputs from vertex shader
layout(location = 0) in vec3 in_WorldPos;
layout(location = 1) in vec3 in_Normal;
layout(location = 2) in vec2 in_UV;
layout(location = 3) in vec4 in_Color;

// Output
layout(location = 0) out vec4 out_Color;

void main()
{
    out_Color = in_Color;
}
)";

Renderer3D::Renderer3D()
{
    scene = NewObject<Scene3D>();
    psoGrid = NewObject<PSOGrid>();
    pso3D = NewObject<PSO3D>();
}

void Renderer3D::Sort()
{
    for (auto viewport : viewports)
    {
        
    }
}

void Renderer3D::Render()
{
    Sort();
    
    for (auto viewport : viewports)
    {
        RenderViewport(viewport);
    }
    
    renderSwapChain->Present(true);
}

void LogCallback(Dg::DEBUG_MESSAGE_SEVERITY severity, const Dg::Char* msg, const Dg::Char* funcName, const Dg::Char* file, int line)
{
    switch (severity)
    {
    case Diligent::DEBUG_MESSAGE_SEVERITY_INFO:
        LogDiligent.Info("{}", msg);
        break;
    case Diligent::DEBUG_MESSAGE_SEVERITY_WARNING:
        LogDiligent.Warn("{}", msg);
        break;
    case Diligent::DEBUG_MESSAGE_SEVERITY_ERROR:
        LogDiligent.Error("{}", msg);
        break;
    case Diligent::DEBUG_MESSAGE_SEVERITY_FATAL_ERROR:
        LogDiligent.Error("{}", msg);
        break;
    }
}

void Renderer3D::RegisterWindow(ObjectPtr<Window> window)
{
    Dg::SwapChainDesc scDesc;
    Dg::IEngineFactoryOpenGL* pFactoryOpenGL = Dg::GetEngineFactoryOpenGL();
    
    Dg::EngineGLCreateInfo engineCI;
    engineCI.Window.hWnd = window->GetWindowNativeID();

    pFactoryOpenGL->SetMessageCallback(&LogCallback);
    pFactoryOpenGL->CreateDeviceAndSwapChainGL(engineCI, &renderDevice, &contextImmediate, scDesc, &renderSwapChain);

    CreateResources();
}

ObjectPtr<Viewport> Renderer3D::NewViewport()
{
    auto viewport = NewObject<Viewport>(renderSwapChain, renderDevice);
    viewports.push_back(viewport);
    return viewport;
}

UUID Renderer3D::MeshCreateFromComponent(StaticMeshComponent* staticMeshComponent)
{
    UUID id = UUID::CreateInvalid();
    
    if (IsValid(scene))
    {
        id = scene->MeshCreateFromComponent(renderDevice, staticMeshComponent);
        staticMeshComponent->rendererMeshID = id;
    }    
    
    return id;
}

void Renderer3D::CreateResources()
{
    psoGrid->Initialize(renderDevice, renderSwapChain);
    pso3D->Initialize(renderDevice, renderSwapChain);
    
    // Pipeline state object encompasses configuration of all GPU stages

    Dg::GraphicsPipelineStateCreateInfo PSOCreateInfo;

    // Pipeline state name is used by the engine to report issues.
    // It is always a good idea to give objects descriptive names.
    PSOCreateInfo.PSODesc.Name = "Simple triangle PSO";

    // This is a graphics pipeline
    PSOCreateInfo.PSODesc.PipelineType = Dg::PIPELINE_TYPE_GRAPHICS;

    // clang-format off
    // This tutorial will render to a single render target
    PSOCreateInfo.GraphicsPipeline.NumRenderTargets             = 1;
    // Set render target format which is the format of the swap chain's color buffer
    PSOCreateInfo.GraphicsPipeline.RTVFormats[0]                = renderSwapChain->GetDesc().ColorBufferFormat;
    // Use the depth buffer format from the swap chain
    PSOCreateInfo.GraphicsPipeline.DSVFormat                    = renderSwapChain->GetDesc().DepthBufferFormat;
    // Primitive topology defines what kind of primitives will be rendered by this pipeline state
    PSOCreateInfo.GraphicsPipeline.PrimitiveTopology            = Dg::PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
    // No back face culling for this tutorial
    PSOCreateInfo.GraphicsPipeline.RasterizerDesc.CullMode      = Dg::CULL_MODE_NONE;
    // Disable depth testing
    PSOCreateInfo.GraphicsPipeline.DepthStencilDesc.DepthEnable = true;
    PSOCreateInfo.GraphicsPipeline.DepthStencilDesc.DepthWriteEnable = true;
    // clang-format on

    Dg::ShaderCreateInfo ShaderCI;
    // Tell the system that the shader source code is in HLSL.
    // For OpenGL, the engine will convert this into GLSL under the hood
    ShaderCI.SourceLanguage = Dg::SHADER_SOURCE_LANGUAGE_GLSL;
    // OpenGL backend requires emulated combined HLSL texture samplers (g_Texture + g_Texture_sampler combination)
    ShaderCI.Desc.UseCombinedTextureSamplers = true;
    // Create a vertex shader
    Dg::RefCntAutoPtr<Dg::IShader> pVS;
    {
        Diligent::RefCntAutoPtr<Dg::IDataBlob> shaderCompilerOutput;
        
        ShaderCI.Desc.ShaderType = Dg::SHADER_TYPE_VERTEX;
        ShaderCI.EntryPoint      = "main";
        ShaderCI.Desc.Name       = "Triangle vertex shader";
        ShaderCI.Source          = VSSource;
        renderDevice->CreateShader(ShaderCI, &pVS, &shaderCompilerOutput);

        if (shaderCompilerOutput)
        {
            LogRenderer3D.Error("An error occurred during vertex shader compilation: {}", (char*)shaderCompilerOutput->GetDataPtr());
        }
    }

    // Create a pixel shader
    Dg::RefCntAutoPtr<Dg::IShader> pPS;
    {
        Diligent::RefCntAutoPtr<Dg::IDataBlob> shaderCompilerOutput;
        
        ShaderCI.Desc.ShaderType = Dg::SHADER_TYPE_PIXEL;
        ShaderCI.EntryPoint      = "main";
        ShaderCI.Desc.Name       = "Triangle pixel shader";
        ShaderCI.Source          = PSSource;
        renderDevice->CreateShader(ShaderCI, &pPS);

        if (shaderCompilerOutput)
        {
            LogRenderer3D.Error("An error occurred during pixel shader compilation: {}", (char*)shaderCompilerOutput->GetDataPtr());
        }
    }

    // Create constant buffer for the vertex shader
    Diligent::BufferDesc VSConstantBufferDesc;
    VSConstantBufferDesc.Name = "VS constants buffer";
    VSConstantBufferDesc.Size = sizeof(VSConstants);
    VSConstantBufferDesc.Usage = Diligent::USAGE_DYNAMIC;
    VSConstantBufferDesc.BindFlags = Diligent::BIND_UNIFORM_BUFFER;
    VSConstantBufferDesc.CPUAccessFlags = Diligent::CPU_ACCESS_WRITE;

    renderDevice->CreateBuffer(VSConstantBufferDesc, nullptr, &vsConstantsBuffer);
    
    // When creating the PSO, make sure to set up the resource layout
    Diligent::PipelineResourceLayoutDesc ResourceLayout;
    Diligent::ShaderResourceVariableDesc Variables[] = {
        {Diligent::SHADER_TYPE_VERTEX, "VSConstants", Diligent::SHADER_RESOURCE_VARIABLE_TYPE_MUTABLE}
    };
    ResourceLayout.Variables = Variables;
    ResourceLayout.NumVariables = _countof(Variables);

    Diligent::LayoutElement LayoutElems[] =
    {
        // Attribute 0 - vertex position
        Diligent::LayoutElement{0, 0, 3, Diligent::VT_FLOAT32, false},
        // Attribute 1 - vertex normal
        Diligent::LayoutElement{1, 0, 3, Diligent::VT_FLOAT32, false},
        // Attribute 2 - texture coordinates
        Diligent::LayoutElement{2, 0, 2, Diligent::VT_FLOAT32, false},
        Diligent::LayoutElement{3, 0, 4, Diligent::VT_FLOAT32, false}
    };
    PSOCreateInfo.GraphicsPipeline.InputLayout.LayoutElements = LayoutElems;
    PSOCreateInfo.GraphicsPipeline.InputLayout.NumElements = _countof(LayoutElems);
    
    PSOCreateInfo.PSODesc.ResourceLayout = ResourceLayout;
    PSOCreateInfo.pVS = pVS;
    PSOCreateInfo.pPS = pPS;
    renderDevice->CreateGraphicsPipelineState(PSOCreateInfo, &pPSO);

    pPSO->CreateShaderResourceBinding(&shaderBinding, true);
    if (auto shaderVarConstants = shaderBinding->GetVariableByName(Diligent::SHADER_TYPE_VERTEX, "VSConstants"))
    {
        shaderVarConstants->Set(vsConstantsBuffer);
    }
}

void Renderer3D::SortViewport(ObjectPtr<Viewport> viewport)
{
    SortViewportChildren(viewport);

    auto world = viewport->GetWorld();
    if (IsValid(world))
    {
        auto registry = world->GetRegistry();
        registry->sort<MaterialComponent>([](const MaterialComponent& c1, const MaterialComponent& c2)
        {
            return c1.material == c2.material;
        });
    }
}

void Renderer3D::SortViewportChildren(ObjectPtr<Viewport> viewport)
{
    for (auto childViewport : viewport->GetChildViewports())
    {
        SortViewportChildren(childViewport);
    }
}

void Renderer3D::RenderViewport(ObjectPtr<Viewport> viewport)
{
    RenderViewportChildren(viewport);
    
    viewport->PreRender(contextImmediate);

    viewport->SetRenderTargetAndClear(contextImmediate);

    auto world = viewport->GetWorld();
    if (IsValid(world))
    {
        Dg::float4x4 mainCameraViewMatrix;
        Dg::float4x4 mainCameraProjectionMatrix;
        
        float viewportRatio = viewport->GetRatio();
        
        auto registry = world->GetRegistry();
        auto viewCameras = registry->view<const TransformComponent, CameraComponent>();
        viewCameras.each([&viewportRatio, &mainCameraProjectionMatrix, &mainCameraViewMatrix](const auto& entity, const TransformComponent& xform, CameraComponent& camera)
        {
            mainCameraViewMatrix = xform.matrix;
            
            camera.ComputeProjectionMatrix(viewportRatio);
            mainCameraProjectionMatrix = camera.frustum;
        });

        if (!viewport->SetRenderTargetAndClear(contextImmediate))
        {
            return;
        }

        psoGrid->Bind(contextImmediate);
        
        auto viewMeshes = registry->view<const TransformComponent, SimpleMeshComponent>();
        viewMeshes.each([&](const auto& entity, const TransformComponent& xform, SimpleMeshComponent& meshComponent)
        {
            // Add debug markers if supported
            contextImmediate->BeginDebugGroup("Mesh Draw");
            
            auto vertexBuffer = scene->GetVertexBuffer(meshComponent.rendererMeshID);
            auto indexBuffer = scene->GetIndexBuffer(meshComponent.rendererMeshID);
        
            // Validate buffers before use
            if (!vertexBuffer || !indexBuffer)
            {
                LogRenderer3D.Error("Invalid buffers for mesh %s", meshComponent.rendererMeshID.ToString().c_str());
                return;
            }
        
            // Validate buffer states
            Dg::BufferDesc vbDesc = vertexBuffer->GetDesc();
            if (!(vbDesc.BindFlags & Dg::BIND_VERTEX_BUFFER))
            {
                LogRenderer3D.Error("Invalid vertex buffer flags");
                return;
            }
            
            // Update constant buffer
            {
                auto psoGridConstants = psoGrid->WriteVS<PSOGrid::PSOConstants>(contextImmediate);
                
                psoGridConstants->world = xform.matrix;
                psoGridConstants->worldViewProj = xform.matrix * mainCameraViewMatrix.Inverse() * mainCameraProjectionMatrix;
                psoGridConstants->cameraPosition = GetPositionFromMatrix(mainCameraViewMatrix);
            }
        
            // Bind vertex buffers
            Diligent::IBuffer* pVBs[] = {vertexBuffer};
            const Uint64 offset   = 0;
            contextImmediate->SetVertexBuffers(0, 1, pVBs, &offset, Diligent::RESOURCE_STATE_TRANSITION_MODE_TRANSITION, Diligent::SET_VERTEX_BUFFERS_FLAG_RESET);
        
            // Bind index buffer
            contextImmediate->SetIndexBuffer(indexBuffer, 0, Dg::RESOURCE_STATE_TRANSITION_MODE_TRANSITION);
        
            //contextImmediate->CommitShaderResources(shaderBinding, Diligent::RESOURCE_STATE_TRANSITION_MODE_TRANSITION);
            psoGrid->Commit(contextImmediate);
            
            uint32 indexCount = scene->GetIndexCount(meshComponent.rendererMeshID);
        
            Dg::DrawIndexedAttribs DrawAttrs;
            DrawAttrs.IndexType  = Diligent::VT_UINT32;
            DrawAttrs.NumIndices = indexCount;
            DrawAttrs.Flags      = Diligent::DRAW_FLAG_VERIFY_ALL; // Enable all validation
            contextImmediate->DrawIndexed(DrawAttrs);
        
            contextImmediate->EndDebugGroup();
        });
    }
    
    viewport->Render(contextImmediate);
}

void Renderer3D::RenderViewportChildren(ObjectPtr<Viewport> viewport)
{
    for (auto childViewport : viewport->GetChildViewports())
    {
        RenderViewport(childViewport);
    }
}
