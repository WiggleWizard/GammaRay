#include "RuntimePCH.h"
#include "WindowViewport.h"

#include "ImGui/ImGuiImplSDLDiligent.h"

#include <imgui.h>

WindowViewport::WindowViewport()
{
}

WindowViewport::WindowViewport(Dg::RefCntAutoPtr<Dg::ISwapChain>& swapChain, Dg::RefCntAutoPtr<Dg::IRenderDevice>& renderDevice)
    : Viewport(swapChain, renderDevice)
{
    
}

bool WindowViewport::PreProcessEvent(const SDL_Event* event)
{
    return imguiRenderer->ProcessEvent(event);
}

void WindowViewport::PreProcess()
{
    Viewport::PreProcess();

    if (imguiRenderer != nullptr)
    {
        imguiRenderer->NewFrame(800, 600, Dg::SURFACE_TRANSFORM_IDENTITY);

        ImGui::ShowDemoWindow();
    }
}

void WindowViewport::Render(Dg::RefCntAutoPtr<Dg::IDeviceContext> deviceContext)
{
    Viewport::Render(deviceContext);

    if (imguiRenderer != nullptr)
    {
        imguiRenderer->EndFrame();
        
        // Set the pipeline state in the immediate context
        //deviceContext->SetPipelineState(pPSO);
        
        imguiRenderer->Render(deviceContext);
    }
}

Dg::RefCntAutoPtr<Dg::ITextureView> WindowViewport::GetRenderViewTarget()
{
    return Dg::RefCntAutoPtr(swapChain->GetCurrentBackBufferRTV());
}

Dg::RefCntAutoPtr<Dg::ITextureView> WindowViewport::GetRenderResourceShader()
{
    return Viewport::GetRenderResourceShader();
}

Dg::RefCntAutoPtr<Dg::ITextureView> WindowViewport::GetViewDepthStencil()
{
    return Dg::RefCntAutoPtr(swapChain->GetDepthBufferDSV());
}

void WindowViewport::SetImguiRenderer(ImGuiImplSDLDiligent* inImguiRenderer)
{
    imguiRenderer.reset(inImguiRenderer);
}
