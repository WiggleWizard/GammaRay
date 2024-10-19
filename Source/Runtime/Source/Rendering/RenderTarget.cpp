#include "RenderTarget.h"

#include <RenderDevice.h>
#include <Texture.h>

RenderTarget::RenderTarget()
{
}

RenderTarget::RenderTarget(Dg::RefCntAutoPtr<Dg::ISwapChain>& swapChain, Dg::RefCntAutoPtr<Dg::IRenderDevice>& renderDevice)
    : swapChain(swapChain)
    , renderDevice(renderDevice)
{
    Resize(500, 500);
}

void RenderTarget::SetRenderTargetAndClear(Dg::IDeviceContext* deviceContext)
{
    Dg::RefCntAutoPtr<Dg::ITextureView> renderViewTarget = GetRenderViewTarget();
        
    // Set render targets before issuing any draw command.
    // Note that Present() unbinds the back buffer if it is set as render target.
    deviceContext->SetRenderTargets(1, &renderViewTarget, GetViewDepthStencil(), Diligent::RESOURCE_STATE_TRANSITION_MODE_TRANSITION);

    // Clear the back buffer
    const float ClearColor[] = {0.350f, 0.350f, 0.350f, 1.0f};
    // Let the engine perform required state transitions
    deviceContext->ClearRenderTarget(renderViewTarget, ClearColor, Diligent::RESOURCE_STATE_TRANSITION_MODE_TRANSITION);
    deviceContext->ClearDepthStencil(GetViewDepthStencil(), Diligent::CLEAR_DEPTH_FLAG, 1.f, 0, Diligent::RESOURCE_STATE_TRANSITION_MODE_TRANSITION);
}

void RenderTarget::Resize(uint32 width, uint32 height)
{
    viewportSize.x = width;
    viewportSize.y = height;
    
    if (swapChain == nullptr)
    {
        return;
    }

    Dg::TextureDesc RTColorDesc;
    RTColorDesc.Name = "Offscreen render target";
    RTColorDesc.Type = Dg::RESOURCE_DIM_TEX_2D;
    RTColorDesc.Width = width;
    RTColorDesc.Height = height;
    RTColorDesc.MipLevels = 1;
    RTColorDesc.Format = Dg::TEX_FORMAT_RGBA8_UNORM_SRGB;
    // The render target can be bound as a shader resource and as a render target
    RTColorDesc.BindFlags = Dg::BIND_SHADER_RESOURCE | Dg::BIND_RENDER_TARGET;
    // Define optimal clear value
    RTColorDesc.ClearValue.Format = RTColorDesc.Format;
    RTColorDesc.ClearValue.Color[0] = 0.350f;
    RTColorDesc.ClearValue.Color[1] = 0.350f;
    RTColorDesc.ClearValue.Color[2] = 0.350f;
    RTColorDesc.ClearValue.Color[3] = 1.f;

    renderDevice->CreateTexture(RTColorDesc, nullptr, &renderTargetTextureColor);
    
    // Store the render target view
    renderViewTarget = renderTargetTextureColor->GetDefaultView(Dg::TEXTURE_VIEW_RENDER_TARGET);
    renderResourceShader = renderTargetTextureColor->GetDefaultView(Dg::TEXTURE_VIEW_SHADER_RESOURCE);

    // Create window-size depth buffer
    Dg::TextureDesc RTDepthDesc = RTColorDesc;
    RTDepthDesc.Name = "Offscreen depth buffer";
    RTDepthDesc.Format = Dg::TEX_FORMAT_D32_FLOAT;
    RTDepthDesc.BindFlags = Dg::BIND_DEPTH_STENCIL;
    // Define optimal clear value
    RTDepthDesc.ClearValue.Format = RTDepthDesc.Format;
    RTDepthDesc.ClearValue.DepthStencil.Depth = 1;
    RTDepthDesc.ClearValue.DepthStencil.Stencil = 0;
    
    Dg::RefCntAutoPtr<Dg::ITexture> pRTDepth;
    renderDevice->CreateTexture(RTDepthDesc, nullptr, &pRTDepth);
    // Store the depth-stencil view
    viewDepthStencil = pRTDepth->GetDefaultView(Dg::TEXTURE_VIEW_DEPTH_STENCIL);
}
