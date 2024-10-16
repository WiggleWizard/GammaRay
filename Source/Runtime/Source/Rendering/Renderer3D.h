#pragma once

#include <RefCntAutoPtr.hpp>
#include <RenderDevice.h>
#include <SwapChain.h>
#include <DeviceContext.h>

class Scene3D;
class Viewport;
class Window;
class WindowViewport;
class StaticMeshComponent;

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
    Renderer3D();
    
    void Render();
    
    void RegisterWindow(ObjectPtr<Window> window);

    ObjectPtr<Viewport> NewViewport();

    template<class T>
    ObjectPtr<T> NewWindowViewport(ObjectPtr<Window> forWindow)
    {
        static_assert(std::is_base_of_v<Viewport, T>, "T must inherit from Viewport");
        
        ObjectPtr<T> viewport = NewObject<T>(renderSwapChain, renderDevice);
        viewports.push_back(Cast<Viewport>(viewport));
        return viewport;
    }

    UUID MeshCreateFromComponent(StaticMeshComponent* staticMeshComponent);

private:
    void CreateResources();

    void RenderViewport(ObjectPtr<Viewport> viewport);
    void RenderViewportChildren(ObjectPtr<Viewport> viewport);
    
    std::vector<ObjectPtr<Viewport>> viewports;

    Dg::RefCntAutoPtr<Dg::IRenderDevice> renderDevice;
    Dg::RefCntAutoPtr<Dg::ISwapChain> renderSwapChain;
    Dg::RefCntAutoPtr<Dg::IDeviceContext> contextImmediate;
    Dg::IPipelineState* pPSO = nullptr;

    ObjectPtr<Scene3D> scene = nullptr;
};
