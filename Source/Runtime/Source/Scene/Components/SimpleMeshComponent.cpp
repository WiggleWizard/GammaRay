#include "SimpleMeshComponent.h"

#include "Engine/Engine.h"
#include "Rendering/Renderer3D.h"

SimpleMeshComponent::SimpleMeshComponent()
{
}

void SimpleMeshComponent::GenerateMesh()
{
    auto renderer = GEngine->GetRenderer3D();
    renderer->MeshCreateFromComponent(this);
}

void SimpleMeshComponent::SetupVertexBuffer(Dg::BufferDesc* descriptor, Dg::BufferData* data)
{
    const size_t vertexCount = 8;
    Vertex* cubeVerts = new Vertex[vertexCount]
    {
        {Dg::float3(-1,-1,-1), Dg::float3(0,0,0), Dg::float2(0,0), Dg::float4(1,0,0,1)},
        {Dg::float3(-1,+1,-1), Dg::float3(0,0,0), Dg::float2(0,0), Dg::float4(0,1,0,1)},
        {Dg::float3(+1,+1,-1), Dg::float3(0,0,0), Dg::float2(0,0), Dg::float4(0,0,1,1)},
        {Dg::float3(+1,-1,-1), Dg::float3(0,0,0), Dg::float2(0,0), Dg::float4(1,1,1,1)},

        {Dg::float3(-1,-1,+1), Dg::float3(0,0,0), Dg::float2(0,0), Dg::float4(1,1,0,1)},
        {Dg::float3(-1,+1,+1), Dg::float3(0,0,0), Dg::float2(0,0), Dg::float4(0,1,1,1)},
        {Dg::float3(+1,+1,+1), Dg::float3(0,0,0), Dg::float2(0,0), Dg::float4(1,0,1,1)},
        {Dg::float3(+1,-1,+1), Dg::float3(0,0,0), Dg::float2(0,0), Dg::float4(0.2f,0.2f,0.2f,1)},
    };

    // Create a vertex buffer that stores cube vertices
    descriptor->Name      = "Cube vertex buffer";
    descriptor->Usage     = Dg::USAGE_IMMUTABLE;
    descriptor->BindFlags = Dg::BIND_VERTEX_BUFFER;
    descriptor->Size      = vertexCount * sizeof(Vertex);
    
    data->pData    = cubeVerts;
    data->DataSize = vertexCount * sizeof(Vertex);
}

uint32 SimpleMeshComponent::SetupIndexBuffer(Dg::BufferDesc* descriptor, Dg::BufferData* data)
{
    const uint32 indexCount = 36;  // 12 triangles * 3 vertices per triangle
    uint32* indices = new uint32[indexCount]
    {
        2,0,1, 2,3,0,
        4,6,5, 4,7,6,
        0,7,4, 0,3,7,
        1,0,4, 1,4,5,
        1,5,2, 5,6,2,
        3,6,7, 3,2,6
    };

    descriptor->Name      = "Cube index buffer";
    descriptor->Usage     = Dg::USAGE_IMMUTABLE;
    descriptor->BindFlags = Dg::BIND_INDEX_BUFFER;
    descriptor->Size      = indexCount * sizeof(uint32);

    data->pData    = indices;
    data->DataSize = indexCount * sizeof(uint32);

    return indexCount;  // returning number of triangles
}
