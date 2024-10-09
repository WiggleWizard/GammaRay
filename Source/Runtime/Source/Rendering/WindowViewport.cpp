#include "RuntimePCH.h"
#include "WindowViewport.h"

WindowViewport::WindowViewport()
{
}

WindowViewport::WindowViewport(Dg::RefCntAutoPtr<Dg::ISwapChain>& swapChain, Dg::RefCntAutoPtr<Dg::IRenderDevice>& renderDevice)
    : Viewport(swapChain, renderDevice)
{
    
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
