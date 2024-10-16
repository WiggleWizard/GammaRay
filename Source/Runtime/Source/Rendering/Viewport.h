#pragma once

#include "RenderTarget.h"

class World;

class ImGuiImplSDLDiligent;
union SDL_Event;

class Viewport : public RenderTarget
{
public:
    Viewport();
    Viewport(Dg::RefCntAutoPtr<Dg::ISwapChain>& swapChain, Dg::RefCntAutoPtr<Dg::IRenderDevice>& renderDevice);

    virtual bool PreProcessEvent(const SDL_Event* event) { return false; }

    virtual void PreProcess() {}
    virtual void Process() {}
    
    virtual void PreRender(Dg::RefCntAutoPtr<Dg::IDeviceContext> deviceContext) {}
    virtual void Render(Dg::RefCntAutoPtr<Dg::IDeviceContext> deviceContext) {}

    virtual void PostPresent() {}

    void SetWorld(ObjectPtr<World> inWorld);
    virtual ObjectPtr<World> GetWorld() { return world; }

    std::vector<ObjectPtr<Viewport>> GetChildViewports();

protected:
    ObjectPtr<World> world = nullptr;
    std::vector<ObjectPtr<Viewport>> children;
};
