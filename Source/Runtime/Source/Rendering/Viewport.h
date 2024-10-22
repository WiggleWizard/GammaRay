#pragma once

#include "RenderTarget.h"

class InputEvent;
class World;

class ImGuiImplSDLDiligent;
union SDL_Event;

class Viewport : public RenderTarget
{
    friend class ImGuiComponentViewport;
    
public:
    Viewport();
    Viewport(Dg::RefCntAutoPtr<Dg::ISwapChain>& swapChain, Dg::RefCntAutoPtr<Dg::IRenderDevice>& renderDevice);

    virtual bool ProcessEventForImGui(const SDL_Event* event) { return false; }

    virtual void PreProcess();
    virtual void Process() {}
    
    virtual void PreRender(Dg::RefCntAutoPtr<Dg::IDeviceContext> deviceContext) {}
    virtual void Render(Dg::RefCntAutoPtr<Dg::IDeviceContext> deviceContext) {}

    virtual void PostPresent() {}

    // Don't override unless you know exactly what you're doing
    virtual bool ProcessInputEvent(const ObjectPtr<InputEvent> inputEvent);

    void SetWorld(ObjectPtr<World> inWorld);
    virtual ObjectPtr<World> GetWorld() { return world; }

    void AttachChildViewport(ObjectPtr<Viewport> viewport);
    std::vector<ObjectPtr<Viewport>> GetChildViewports();

protected:
    virtual void OnInputEvent(const ObjectPtr<InputEvent> inputEvent);
    
    ObjectPtr<World> world = nullptr;
    std::vector<ObjectPtr<Viewport>> children;
    bool mouseFocused = false;
};
