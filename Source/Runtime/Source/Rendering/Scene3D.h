#pragma once

class StaticMeshComponent;

namespace Diligent
{
    struct IBuffer;
    struct IRenderDevice;
}

class Scene3D : public Object
{
public:
    Scene3D();

    UUID MeshCreateFromComponent(Dg::RefCntAutoPtr<Dg::IRenderDevice> device, StaticMeshComponent* staticMeshComponent);

protected:
    std::unordered_map<UUID, Dg::RefCntAutoPtr<Dg::IBuffer>> vertexBuffers;
    std::unordered_map<UUID, Dg::RefCntAutoPtr<Dg::IBuffer>> indexBuffers;
};
