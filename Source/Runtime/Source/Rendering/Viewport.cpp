#include "Viewport.h"

Viewport::Viewport()
{
}

Viewport::Viewport(Dg::RefCntAutoPtr<Dg::ISwapChain>& swapChain, Dg::RefCntAutoPtr<Dg::IRenderDevice>& renderDevice)
    : RenderTarget(swapChain, renderDevice)
{
}

bool Viewport::ProcessInputEvent(const InputEvent* inputEvent)
{
    return false;
}

void Viewport::SetWorld(ObjectPtr<World> inWorld)
{
    world = inWorld;
}

void Viewport::AttachChildViewport(ObjectPtr<Viewport> viewport)
{
    children.push_back(viewport);
}

std::vector<ObjectPtr<Viewport>> Viewport::GetChildViewports()
{
    return children;
}
