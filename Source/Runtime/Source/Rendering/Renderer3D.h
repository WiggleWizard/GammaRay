#pragma once

#include <RefCntAutoPtr.hpp>
#include <RenderDevice.h>
#include <SwapChain.h>

class Viewport;
class Window;
class WindowViewport;

namespace Diligent
{
    struct ITexture;
    struct ITextureView;
    struct IDeviceContext;
    struct IPipelineState;
}
namespace Dg = Diligent;

class Renderer3D : public Object
{
public:
    void Render();
    
    void RegisterWindow(ObjectPtr<Window> window);

    ObjectPtr<Viewport> NewViewport();
    ObjectPtr<WindowViewport> NewWindowViewport(ObjectPtr<Window> forWindow);

private:
    void CreateResources();
    
    std::vector<ObjectPtr<Viewport>> viewports;

    Dg::RefCntAutoPtr<Dg::IRenderDevice> renderDevice;
    Dg::RefCntAutoPtr<Dg::ISwapChain> renderSwapChain;
    Dg::IDeviceContext* contextImmediate = nullptr;
    Dg::IPipelineState* pPSO = nullptr;
};
