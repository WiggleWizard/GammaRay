#pragma once

#include <BasicMath.hpp>
#include <RefCntAutoPtr.hpp>

namespace Diligent
{
    struct IRenderDevice;
    struct ISwapChain;
    struct ITexture;
    struct ITextureView;
    struct IDeviceContext;
}
namespace Dg = Diligent;

// The actual offscreen "texture" holder
class RenderTarget : public Object
{
public:
    RenderTarget();
    RenderTarget(Dg::RefCntAutoPtr<Dg::ISwapChain> swapChain, Dg::RefCntAutoPtr<Dg::IRenderDevice> renderDevice);

    Dg::RefCntAutoPtr<Dg::ITextureView> GetRenderViewTarget() { return renderViewTarget; }
    Dg::RefCntAutoPtr<Dg::ITextureView> GetRenderResourceShader() { return renderResourceShader; }
    Dg::RefCntAutoPtr<Dg::ITextureView> GetViewDepthStencil() { return viewDepthStencil; }

    void SetRenderTargetAndClear(Dg::IDeviceContext* deviceContext);
    
    virtual void Resize(uint32 width, uint32 height);
    
private:
    Dg::RefCntAutoPtr<Dg::ISwapChain> swapChain;
    Dg::RefCntAutoPtr<Dg::IRenderDevice> renderDevice;
    
    Dg::RefCntAutoPtr<Dg::ITexture> renderTargetTextureColor;
    Dg::RefCntAutoPtr<Dg::ITextureView> renderViewTarget;
    Dg::RefCntAutoPtr<Dg::ITextureView> renderResourceShader;
    Dg::RefCntAutoPtr<Dg::ITextureView> viewDepthStencil;

    Dg::Vector2<uint32> viewportSize;
};
