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
    RenderTarget(Dg::RefCntAutoPtr<Dg::ISwapChain>& swapChain, Dg::RefCntAutoPtr<Dg::IRenderDevice>& renderDevice);

    Dg::RefCntAutoPtr<Dg::ISwapChain> GetSwapChain() { return swapChain; }
    Dg::RefCntAutoPtr<Dg::IRenderDevice> GetRenderDevice() { return renderDevice; }
    virtual Dg::RefCntAutoPtr<Dg::ITextureView> GetRenderViewTarget() { return renderViewTarget; }
    virtual Dg::RefCntAutoPtr<Dg::ITextureView> GetRenderResourceShader() { return renderResourceShader; }
    virtual Dg::RefCntAutoPtr<Dg::ITextureView> GetViewDepthStencil() { return viewDepthStencil; }

    // Sets the render target to this render target and return true if it was successful
    bool SetRenderTargetAndClear(Dg::IDeviceContext* deviceContext);
    
    virtual void Resize(uint32 width, uint32 height);
    float GetHorizontalRatio();
    float GetVerticalRatio();
    float GetRatio();
    
protected:
    Dg::RefCntAutoPtr<Dg::ISwapChain> swapChain;
    Dg::RefCntAutoPtr<Dg::IRenderDevice> renderDevice;
    
    Dg::RefCntAutoPtr<Dg::ITexture> renderTargetTextureColor;
    Dg::RefCntAutoPtr<Dg::ITextureView> renderViewTarget;
    Dg::RefCntAutoPtr<Dg::ITextureView> renderResourceShader;
    Dg::RefCntAutoPtr<Dg::ITextureView> viewDepthStencil;

    Dg::Vector2<uint32> viewportSize;
};
