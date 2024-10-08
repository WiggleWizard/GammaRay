#include "Window.h"

#include "../../Thirdparty/DiligentTools/Imgui/interface/ImGuiImplWin32.hpp"
#include "../../ThirdParty/DiligentTools/ThirdParty/imgui/imgui.h"
#include "Rendering/ImGui/ImGuiImplSDLDiligent.h"
#include "UI/ImGuiComponentViewport.h"

#include <SDL.h>
#include <SDL_syswm.h>
#include <Common/interface/RefCntAutoPtr.hpp>

#include <Graphics/GraphicsEngineOpenGL/interface/EngineFactoryOpenGL.h>

namespace Dg = Diligent;

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




void Present()
{
    
}

Window::Window(const String& windowTitle)
{
    windowPtr = SDL_CreateWindow(windowTitle.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
    
    Diligent::SwapChainDesc scDesc;
    auto* pFactoryOpenGL = Diligent::GetEngineFactoryOpenGL();
    
    Diligent::EngineGLCreateInfo engineCI;
    engineCI.Window.hWnd = GetWindowNativeID();

    pFactoryOpenGL->CreateDeviceAndSwapChainGL(engineCI, &pDevice, &pImmediateContext, scDesc, &pSwapChain);

    CreateResources();
}

Window::~Window()
{
}

uint32 Window::GetWindowID()
{
    uint32 windowID = 0;
    
    if (windowPtr != nullptr)
    {
        windowID = SDL_GetWindowID(windowPtr);
    }

    return windowID;
}

void* Window::GetWindowNativeID()
{
    SDL_SysWMinfo wmInfo;
    SDL_VERSION(&wmInfo.version);
    SDL_GetWindowWMInfo(windowPtr, &wmInfo);
    return (void*)wmInfo.info.win.window;
}

bool Window::PreProcessEvent(const SDL_Event* event)
{
    return imguiRenderer->ProcessEvent(event);
}

void Window::OnCloseRequested()
{
    
}

bool Window::IsFocused() const
{
    const uint32 windowFlags = SDL_GetWindowFlags(windowPtr);
    return (windowFlags & SDL_WINDOW_INPUT_FOCUS) != 0;
}

void Window::PreProcess()
{
    Render();
    Present();
}

void Window::Render()
{
    // // Set render targets before issuing any draw command.
    // // Note that Present() unbinds the back buffer if it is set as render target.
    // pImmediateContext->SetRenderTargets(1, &viewport->GetRenderViewTarget(), viewport->GetViewDepthStencil(), Diligent::RESOURCE_STATE_TRANSITION_MODE_TRANSITION);
    //
    // // Clear the back buffer
    // const float ClearColor[] = {0.350f, 0.350f, 0.350f, 1.0f};
    // // Let the engine perform required state transitions
    // pImmediateContext->ClearRenderTarget(viewport->GetRenderViewTarget(), ClearColor, Diligent::RESOURCE_STATE_TRANSITION_MODE_TRANSITION);
    // pImmediateContext->ClearDepthStencil(viewport->GetViewDepthStencil(), Diligent::CLEAR_DEPTH_FLAG, 1.f, 0, Diligent::RESOURCE_STATE_TRANSITION_MODE_TRANSITION);
    //
    // // Set the pipeline state in the immediate context
    // pImmediateContext->SetPipelineState(pPSO);
    //
    // // Typically we should now call CommitShaderResources(), however shaders in this example don't
    // // use any resources.
    //
    // Diligent::DrawAttribs drawAttrs;
    // drawAttrs.NumVertices = 3; // Render 3 vertices
    // pImmediateContext->Draw(drawAttrs);
    //
    //
    //
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
    //
    // pSwapChain->Present(true);
}

void Window::OnWindowEvent(const SDL_WindowEvent* event)
{
}

void Window::OnMouseMove(const SDL_MouseMotionEvent* event)
{
}

void Window::OnMouseButtonPressed(const SDL_MouseButtonEvent* event)
{
}

void Window::OnMouseWheel(const SDL_MouseWheelEvent* event)
{
}

void Window::OnKeyboardPressed(const SDL_KeyboardEvent* event)
{
}

void Window::OnJoyAxisMotion(SDL_JoyAxisEvent* event)
{
}

void Window::OnJoyButtonPressed(SDL_JoyButtonEvent* event)
{
}

void Window::OnTextInput(const SDL_TextInputEvent* event)
{
}

void Window::AttachViewport(ObjectPtr<WindowViewport> inViewport)
{
    viewport = inViewport;
}

void Window::CreateResources()
{
    // Pipeline state object encompasses configuration of all GPU stages

    Diligent::GraphicsPipelineStateCreateInfo PSOCreateInfo;

    // Pipeline state name is used by the engine to report issues.
    // It is always a good idea to give objects descriptive names.
    PSOCreateInfo.PSODesc.Name = "Simple triangle PSO";

    // This is a graphics pipeline
    PSOCreateInfo.PSODesc.PipelineType = Diligent::PIPELINE_TYPE_GRAPHICS;

    // clang-format off
    // This tutorial will render to a single render target
    PSOCreateInfo.GraphicsPipeline.NumRenderTargets             = 1;
    // Set render target format which is the format of the swap chain's color buffer
    PSOCreateInfo.GraphicsPipeline.RTVFormats[0]                = pSwapChain->GetDesc().ColorBufferFormat;
    // Use the depth buffer format from the swap chain
    PSOCreateInfo.GraphicsPipeline.DSVFormat                    = pSwapChain->GetDesc().DepthBufferFormat;
    // Primitive topology defines what kind of primitives will be rendered by this pipeline state
    PSOCreateInfo.GraphicsPipeline.PrimitiveTopology            = Diligent::PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
    // No back face culling for this tutorial
    PSOCreateInfo.GraphicsPipeline.RasterizerDesc.CullMode      = Diligent::CULL_MODE_NONE;
    // Disable depth testing
    PSOCreateInfo.GraphicsPipeline.DepthStencilDesc.DepthEnable = Diligent::False;
    // clang-format on

    Diligent::ShaderCreateInfo ShaderCI;
    // Tell the system that the shader source code is in HLSL.
    // For OpenGL, the engine will convert this into GLSL under the hood
    ShaderCI.SourceLanguage = Diligent::SHADER_SOURCE_LANGUAGE_HLSL;
    // OpenGL backend requires emulated combined HLSL texture samplers (g_Texture + g_Texture_sampler combination)
    ShaderCI.Desc.UseCombinedTextureSamplers = true;
    // Create a vertex shader
    Diligent::RefCntAutoPtr<Diligent::IShader> pVS;
    {
        ShaderCI.Desc.ShaderType = Diligent::SHADER_TYPE_VERTEX;
        ShaderCI.EntryPoint      = "main";
        ShaderCI.Desc.Name       = "Triangle vertex shader";
        ShaderCI.Source          = VSSource;
        pDevice->CreateShader(ShaderCI, &pVS);
    }

    // Create a pixel shader
    Diligent::RefCntAutoPtr<Diligent::IShader> pPS;
    {
        ShaderCI.Desc.ShaderType = Diligent::SHADER_TYPE_PIXEL;
        ShaderCI.EntryPoint      = "main";
        ShaderCI.Desc.Name       = "Triangle pixel shader";
        ShaderCI.Source          = PSSource;
        pDevice->CreateShader(ShaderCI, &pPS);
    }

    // Finally, create the pipeline state
    PSOCreateInfo.pVS = pVS;
    PSOCreateInfo.pPS = pPS;
    pDevice->CreateGraphicsPipelineState(PSOCreateInfo, &pPSO);

    auto scDesc = pSwapChain->GetDesc();

    Diligent::ImGuiDiligentCreateInfo imguiCreateInfo;
    imguiCreateInfo.pDevice = pDevice;
    imguiCreateInfo.BackBufferFmt = scDesc.ColorBufferFormat;
    imguiCreateInfo.DepthBufferFmt = scDesc.DepthBufferFormat;
    imguiRenderer.reset(new ImGuiImplSDLDiligent(imguiCreateInfo, windowPtr));

    //renderTarget = NewObject<RenderTarget>(pSwapChain, pDevice);
    
    viewport = NewObject<ImGuiComponentViewport>(renderTarget);
}
