#pragma once

#include <RefCntAutoPtr.hpp>

#include "ImGuiComponent.h"

namespace Diligent
{
    struct IRenderDevice;
    struct ISwapChain;
    struct ITexture;
    struct ITextureView;
}
using namespace Diligent;

class ImGuiComponentViewport : public ImGuiComponent
{
public:
    ImGuiComponentViewport(RefCntAutoPtr<ISwapChain> swapChain, RefCntAutoPtr<IRenderDevice> renderDevice);
    
    virtual void Draw() override;
    
    void OnResized();

    RefCntAutoPtr<ITextureView> GetRenderViewTarget() { return renderViewTarget; }
    RefCntAutoPtr<ITextureView> GetRenderResourceShader() { return renderResourceShader; }
    RefCntAutoPtr<ITextureView> GetViewDepthStencil() { return viewDepthStencil; }

private:
    RefCntAutoPtr<ISwapChain> swapChain;
    RefCntAutoPtr<IRenderDevice> renderDevice;
    
    RefCntAutoPtr<ITexture> renderTargetTextureColor;
    RefCntAutoPtr<ITextureView> renderViewTarget;
    RefCntAutoPtr<ITextureView> renderResourceShader;
    RefCntAutoPtr<ITextureView> viewDepthStencil;
    
    UUID uuid;
};
