#include "Renderer3D.h"

#include "ImGui/ImGuiImplSDLDiligent.h"
#include "Windowing/Window.h"
#include "Rendering/Viewport.h"
#include "Rendering/WindowViewport.h"

#include <GraphicsTypes.h>
#include <ImGuiImplDiligent.hpp>

#include <Graphics/GraphicsEngine/interface/SwapChain.h>
#include <Graphics/GraphicsEngineOpenGL/interface/EngineFactoryOpenGL.h>

static const char* VSSource = R"(
struct PSInput 
{ 
    float4 Pos   : SV_POSITION; 
    float3 Color : COLOR; 
};

void main(in uint VertId : SV_VertexID, out PSInput PSIn) 
{
    float4 Pos[3];
    Pos[0] = float4(-0.5, -0.5, 0.0, 1.0);
    Pos[1] = float4( 0.0, +0.5, 0.0, 1.0);
    Pos[2] = float4(+0.5, -0.5, 0.0, 1.0);

    float3 Col[3];
    Col[0] = float3(1.0, 0.0, 0.0); // red
    Col[1] = float3(0.0, 1.0, 0.0); // green
    Col[2] = float3(0.0, 0.0, 1.0); // blue

    PSIn.Pos   = Pos[VertId];
    PSIn.Color = Col[VertId];
}
)";

// Pixel shader simply outputs interpolated vertex color
static const char* PSSource = R"(
struct PSInput 
{ 
    float4 Pos   : SV_POSITION; 
    float3 Color : COLOR; 
};

struct PSOutput
{ 
    float4 Color : SV_TARGET; 
};

void main(in PSInput  PSIn, out PSOutput PSOut)
{
    PSOut.Color = float4(PSIn.Color.rgb, 1.0);
}
)";

void Renderer3D::Render()
{
    for (auto viewport : viewports)
    {
        viewport->PreRender(contextImmediate);
        
        // Set render targets before issuing any draw command.
        // Note that Present() unbinds the back buffer if it is set as render target.
        contextImmediate->SetRenderTargets(1, &viewport->GetRenderViewTarget(), viewport->GetViewDepthStencil(), Diligent::RESOURCE_STATE_TRANSITION_MODE_TRANSITION);
        
        // Clear the back buffer
        const float ClearColor[] = {0.350f, 0.350f, 0.350f, 1.0f};
        // Let the engine perform required state transitions
        contextImmediate->ClearRenderTarget(viewport->GetRenderViewTarget(), ClearColor, Diligent::RESOURCE_STATE_TRANSITION_MODE_TRANSITION);
        contextImmediate->ClearDepthStencil(viewport->GetViewDepthStencil(), Diligent::CLEAR_DEPTH_FLAG, 1.f, 0, Diligent::RESOURCE_STATE_TRANSITION_MODE_TRANSITION);
        
        // Set the pipeline state in the immediate context
        contextImmediate->SetPipelineState(pPSO);
        
        // Typically we should now call CommitShaderResources(), however shaders in this example don't
        // use any resources.
        
        Diligent::DrawAttribs drawAttrs;
        drawAttrs.NumVertices = 3; // Render 3 vertices
        contextImmediate->Draw(drawAttrs);
        
        
        
        // auto scDesc = pSwapChain->GetDesc();
        // imguiRenderer->NewFrame(scDesc.Width, scDesc.Height, scDesc.PreTransform);
        //
        // auto* pRTV = pSwapChain->GetCurrentBackBufferRTV();
        // auto* pDSV = pSwapChain->GetDepthBufferDSV();
        // pImmediateContext->SetRenderTargets(1, &pRTV, pDSV, Diligent::RESOURCE_STATE_TRANSITION_MODE_TRANSITION);
        // pImmediateContext->ClearRenderTarget(pRTV, ClearColor, Diligent::RESOURCE_STATE_TRANSITION_MODE_TRANSITION);
        // pImmediateContext->ClearDepthStencil(pDSV, Diligent::CLEAR_DEPTH_FLAG, 1.f, 0, Diligent::RESOURCE_STATE_TRANSITION_MODE_TRANSITION);
        //
        // static bool showDemoWindow = true;
        // ImGui::ShowDemoWindow(&showDemoWindow);
        // viewport->Draw();
        //
        // imguiRenderer->Render(pImmediateContext);
        
        viewport->Render(contextImmediate);
    }
    
    renderSwapChain->Present(true);
}

void Renderer3D::RegisterWindow(ObjectPtr<Window> window)
{
    Dg::SwapChainDesc scDesc;
    Dg::IEngineFactoryOpenGL* pFactoryOpenGL = Dg::GetEngineFactoryOpenGL();
    
    Dg::EngineGLCreateInfo engineCI;
    engineCI.Window.hWnd = window->GetWindowNativeID();

    pFactoryOpenGL->CreateDeviceAndSwapChainGL(engineCI, &renderDevice, &contextImmediate, scDesc, &renderSwapChain);

    CreateResources();
}

ObjectPtr<Viewport> Renderer3D::NewViewport()
{
    auto viewport = NewObject<Viewport>(renderSwapChain, renderDevice);
    viewports.push_back(viewport);
    return viewport;
}

void Renderer3D::CreateResources()
{
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
    PSOCreateInfo.GraphicsPipeline.DepthStencilDesc.DepthEnable = Dg::False;
    // clang-format on

    Dg::ShaderCreateInfo ShaderCI;
    // Tell the system that the shader source code is in HLSL.
    // For OpenGL, the engine will convert this into GLSL under the hood
    ShaderCI.SourceLanguage = Dg::SHADER_SOURCE_LANGUAGE_HLSL;
    // OpenGL backend requires emulated combined HLSL texture samplers (g_Texture + g_Texture_sampler combination)
    ShaderCI.Desc.UseCombinedTextureSamplers = true;
    // Create a vertex shader
    Dg::RefCntAutoPtr<Dg::IShader> pVS;
    {
        ShaderCI.Desc.ShaderType = Dg::SHADER_TYPE_VERTEX;
        ShaderCI.EntryPoint      = "main";
        ShaderCI.Desc.Name       = "Triangle vertex shader";
        ShaderCI.Source          = VSSource;
        renderDevice->CreateShader(ShaderCI, &pVS);
    }

    // Create a pixel shader
    Dg::RefCntAutoPtr<Dg::IShader> pPS;
    {
        ShaderCI.Desc.ShaderType = Dg::SHADER_TYPE_PIXEL;
        ShaderCI.EntryPoint      = "main";
        ShaderCI.Desc.Name       = "Triangle pixel shader";
        ShaderCI.Source          = PSSource;
        renderDevice->CreateShader(ShaderCI, &pPS);
    }

    // Finally, create the pipeline state
    PSOCreateInfo.pVS = pVS;
    PSOCreateInfo.pPS = pPS;
    renderDevice->CreateGraphicsPipelineState(PSOCreateInfo, &pPSO);

    auto scDesc = renderSwapChain->GetDesc();

    // Dg::ImGuiDiligentCreateInfo imguiCreateInfo;
    // imguiCreateInfo.pDevice = pDevice;
    // imguiCreateInfo.BackBufferFmt = scDesc.ColorBufferFormat;
    // imguiCreateInfo.DepthBufferFmt = scDesc.DepthBufferFormat;
    // imguiRenderer.reset(new ImGuiImplSDLDiligent(imguiCreateInfo, windowPtr));

    //renderTarget = NewObject<RenderTarget>(pSwapChain, pDevice);
    
    // viewport = NewObject<ImGuiComponentViewport>(renderTarget);
}
