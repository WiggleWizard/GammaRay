#include "ImGuiComponentViewport.h"

#include <imgui.h>
#include <SwapChain.h>
#include <RenderDevice.h>

using namespace Diligent;

ImGuiComponentViewport::ImGuiComponentViewport(RefCntAutoPtr<ISwapChain> swapChain, RefCntAutoPtr<IRenderDevice> renderDevice)
    : swapChain(swapChain)
    , renderDevice(renderDevice)
{
    OnResized();
}

void ImGuiComponentViewport::Draw()
{
    ImGui::PushID(uuid.ToString().c_str());
    
    if (ImGui::Begin("Viewport"))
    {
        ImGui::Image(renderResourceShader, ImGui::GetContentRegionAvail());
    }
    ImGui::End();

    ImGui::PopID();
}

void ImGuiComponentViewport::OnResized()
{
    if (swapChain == nullptr)
    {
        return;
    }

    TextureDesc RTColorDesc;
    RTColorDesc.Name = "Offscreen render target";
    RTColorDesc.Type = RESOURCE_DIM_TEX_2D;
    RTColorDesc.Width = 500;
    RTColorDesc.Height = 500;
    RTColorDesc.MipLevels = 1;
    RTColorDesc.Format = TEX_FORMAT_RGBA8_UNORM_SRGB;
    // The render target can be bound as a shader resource and as a render target
    RTColorDesc.BindFlags = BIND_SHADER_RESOURCE | BIND_RENDER_TARGET;
    // Define optimal clear value
    RTColorDesc.ClearValue.Format = RTColorDesc.Format;
    RTColorDesc.ClearValue.Color[0] = 0.350f;
    RTColorDesc.ClearValue.Color[1] = 0.350f;
    RTColorDesc.ClearValue.Color[2] = 0.350f;
    RTColorDesc.ClearValue.Color[3] = 1.f;

    renderDevice->CreateTexture(RTColorDesc, nullptr, &renderTargetTextureColor);
    
    // Store the render target view
    renderViewTarget = renderTargetTextureColor->GetDefaultView(TEXTURE_VIEW_RENDER_TARGET);
    renderResourceShader = renderTargetTextureColor->GetDefaultView(TEXTURE_VIEW_SHADER_RESOURCE);

    // Create window-size depth buffer
    TextureDesc RTDepthDesc = RTColorDesc;
    RTDepthDesc.Name = "Offscreen depth buffer";
    RTDepthDesc.Format = TEX_FORMAT_D32_FLOAT;
    RTDepthDesc.BindFlags = BIND_DEPTH_STENCIL;
    // Define optimal clear value
    RTDepthDesc.ClearValue.Format = RTDepthDesc.Format;
    RTDepthDesc.ClearValue.DepthStencil.Depth = 1;
    RTDepthDesc.ClearValue.DepthStencil.Stencil = 0;
    
    RefCntAutoPtr<ITexture> pRTDepth;
    renderDevice->CreateTexture(RTDepthDesc, nullptr, &pRTDepth);
    // Store the depth-stencil view
    viewDepthStencil = pRTDepth->GetDefaultView(TEXTURE_VIEW_DEPTH_STENCIL);
}
