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

    Dg::RefCntAutoPtr<Dg::IBuffer> GetVertexBuffer(UUID meshId);
    Dg::RefCntAutoPtr<Dg::IBuffer> GetIndexBuffer(UUID meshId);
    uint32 GetIndexCount(UUID meshId);

protected:
    std::unordered_map<UUID, Dg::RefCntAutoPtr<Dg::IBuffer>> vertexBuffers;
    std::unordered_map<UUID, Dg::RefCntAutoPtr<Dg::IBuffer>> indexBuffers;
    std::unordered_map<UUID, uint32> indexCounts;
};
