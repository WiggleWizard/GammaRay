#include "RuntimePCH.h"
#include "Scene3D.h"

#include "Scene/Components/StaticMeshComponent.h"

#include <Graphics/GraphicsTools/interface/MapHelper.hpp>

DEFINE_LOGGER_STATIC(LogScene3D, LogVerbosity::Fatal)

Scene3D::Scene3D()
{
}

UUID Scene3D::MeshCreateFromComponent(Dg::RefCntAutoPtr<Dg::IRenderDevice> device, StaticMeshComponent* staticMeshComponent)
{
    const UUID id;

    if (!id.IsValid())
    {
        return id;
    }

    if (device == nullptr)
    {
        LogScene3D.Error("Device nullptr");
        return UUID::CreateInvalid();
    }
    
    // Set up and populate vertex buffer
    Dg::BufferDesc vertBufferDesc;
    Dg::BufferData vertBufferData;
    staticMeshComponent->SetupVertexBuffer(&vertBufferDesc, &vertBufferData);

    Dg::RefCntAutoPtr<Dg::IBuffer> vertexBuffer;
    device->CreateBuffer(vertBufferDesc, &vertBufferData, &vertexBuffer);
    vertexBuffers.insert_or_assign(id, vertexBuffer);

    // Index buffer
    const SharedPtr<Dg::BufferDesc> indexBufferDesc(new Dg::BufferDesc());
    const SharedPtr<Dg::BufferData> indexBufferData(new Dg::BufferData());
    uint32 indexCount = staticMeshComponent->SetupIndexBuffer(indexBufferDesc.get(), indexBufferData.get());

    Dg::RefCntAutoPtr<Dg::IBuffer> indexBuffer;
    device->CreateBuffer(*indexBufferDesc, indexBufferData.get(), &indexBuffer);
    indexBuffers.insert_or_assign(id, indexBuffer);

    indexCounts.insert_or_assign(id, indexCount);

    return id;
}

Dg::RefCntAutoPtr<Dg::IBuffer> Scene3D::GetVertexBuffer(UUID meshId)
{
    return vertexBuffers[meshId];
}

Dg::RefCntAutoPtr<Dg::IBuffer> Scene3D::GetIndexBuffer(UUID meshId)
{
    return indexBuffers[meshId];
}

uint32 Scene3D::GetIndexCount(UUID meshId)
{
    return indexCounts[meshId];
}
