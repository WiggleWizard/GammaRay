#pragma once

#include "Viewport.h"

class WindowViewport : public Viewport
{
public:
    WindowViewport();
    WindowViewport(Dg::RefCntAutoPtr<Dg::ISwapChain>& swapChain, Dg::RefCntAutoPtr<Dg::IRenderDevice>& renderDevice);

    virtual bool PreProcessEvent(const SDL_Event* event) override;
    virtual void PreProcess() override;
    virtual void Render(Dg::RefCntAutoPtr<Dg::IDeviceContext> deviceContext) override;

    virtual Dg::RefCntAutoPtr<Dg::ITextureView> GetRenderViewTarget() override;
    virtual Dg::RefCntAutoPtr<Dg::ITextureView> GetRenderResourceShader() override;
    virtual Dg::RefCntAutoPtr<Dg::ITextureView> GetViewDepthStencil() override;

    virtual void SetImguiRenderer(ImGuiImplSDLDiligent* inImguiRenderer);

protected:
    virtual void DrawImGui();
    
    std::shared_ptr<ImGuiImplSDLDiligent> imguiRenderer = nullptr;
};
