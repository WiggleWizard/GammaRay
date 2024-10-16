#include "Viewport.h"

Viewport::Viewport()
{
}

Viewport::Viewport(Dg::RefCntAutoPtr<Dg::ISwapChain>& swapChain, Dg::RefCntAutoPtr<Dg::IRenderDevice>& renderDevice)
    : RenderTarget(swapChain, renderDevice)
{
}

void Viewport::SetWorld(ObjectPtr<World> inWorld)
{
    world = inWorld;
}

std::vector<ObjectPtr<Viewport>> Viewport::GetChildViewports()
{
    return children;
}
