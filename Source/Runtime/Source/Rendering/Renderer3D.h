#pragma once

#include <RefCntAutoPtr.hpp>

class Viewport;
class Window;

namespace Diligent
{
    class IRenderDevice;
    class ISwapChain;
    class IDeviceContext;
    class IPipelineState;
}
namespace Dg = Diligent;

class Renderer3D : public Object
{
public:
    void Render();

    void OnWindowCreated(ObjectPtr<Window> window);
    void RegisterViewport(ObjectPtr<Viewport> viewport);

private:
    std::vector<ObjectPtr<Viewport>> viewports;

    Dg::RefCntAutoPtr<Dg::IRenderDevice> pDevice;
    Dg::RefCntAutoPtr<Dg::ISwapChain> pSwapChain;
    Dg::IDeviceContext* pImmediateContext = nullptr;
    Dg::IPipelineState* pPSO = nullptr;
};
