#include "Viewport.h"

Viewport::Viewport()
{
}

Viewport::Viewport(Dg::RefCntAutoPtr<Dg::ISwapChain> swapChain, Dg::RefCntAutoPtr<Dg::IRenderDevice> renderDevice)
    : RenderTarget(swapChain, renderDevice)
{
}
