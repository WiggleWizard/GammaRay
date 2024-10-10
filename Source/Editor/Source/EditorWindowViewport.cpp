#include "EditorWindowViewport.h"

EditorWindowViewport::EditorWindowViewport(Dg::RefCntAutoPtr<Dg::ISwapChain>& swapChain, Dg::RefCntAutoPtr<Dg::IRenderDevice>& renderDevice)
    : Super(swapChain, renderDevice)
{
}
