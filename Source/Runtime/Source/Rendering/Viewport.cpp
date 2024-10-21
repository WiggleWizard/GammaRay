#include "Viewport.h"

Viewport::Viewport()
{
}

Viewport::Viewport(Dg::RefCntAutoPtr<Dg::ISwapChain>& swapChain, Dg::RefCntAutoPtr<Dg::IRenderDevice>& renderDevice)
    : RenderTarget(swapChain, renderDevice)
{
}

void Viewport::PreProcess()
{
    for (auto viewport : children)
    {
        viewport->PreProcess();
    }
}

bool Viewport::ProcessInputEvent(const ObjectPtr<InputEvent> inputEvent)
{
    // Iterate through all child viewports and inform them of the input to handle it
    // TODO: Defined ordering
    for (auto& viewport : children)
    {
        viewport->ProcessInputEvent(inputEvent);
    }

    // Finally, handle it internally
    OnInputEvent(inputEvent);

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

void Viewport::OnInputEvent(const ObjectPtr<InputEvent> inputEvent)
{
    
}
