#include "RuntimePCH.h"
#include "Scene3D.h"

#include "Scene/Components/StaticMeshComponent.h"

DEFINE_LOGGER_STATIC(LogScene3D, LogVerbosity::Fatal)

Scene3D::Scene3D()
{
}

UUID Scene3D::MeshCreateFromComponent(Dg::RefCntAutoPtr<Dg::IRenderDevice> device, StaticMeshComponent* staticMeshComponent)
{
    const UUID id;

    if (device == nullptr)
    {
        LogScene3D.Error("Device nullptr");
        return UUID::CreateInvalid();
    }
    
    // Set up and populate vertex buffer
    const SharedPtr<Dg::BufferDesc> vertBufferDesc(new Dg::BufferDesc());
    const SharedPtr<Dg::BufferData> vertBufferData(new Dg::BufferData());
    staticMeshComponent->SetupVertexBuffer(vertBufferDesc.get(), vertBufferData.get());

    Dg::RefCntAutoPtr<Dg::IBuffer> vertexBuffer;
    device->CreateBuffer(*vertBufferDesc, vertBufferData.get(), &vertexBuffer);
    vertexBuffers.insert_or_assign(id, vertexBuffer);

    // Index buffer
    const SharedPtr<Dg::BufferDesc> indexBufferDesc(new Dg::BufferDesc());
    const SharedPtr<Dg::BufferData> indexBufferData(new Dg::BufferData());
    staticMeshComponent->SetupIndexBuffer(indexBufferDesc.get(), indexBufferData.get());

    Dg::RefCntAutoPtr<Dg::IBuffer> indexBuffer;
    device->CreateBuffer(*indexBufferDesc, indexBufferData.get(), &indexBuffer);
    indexBuffers.insert_or_assign(id, indexBuffer);

    return id;
}
