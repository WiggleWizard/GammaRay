#include "SimpleMeshComponent.h"

#include "Engine/Engine.h"
#include "Rendering/Renderer3D.h"

SimpleMeshComponent::SimpleMeshComponent()
{
}

void SimpleMeshComponent::GenerateMesh(const Shape inShape)
{
    shape = inShape;

    auto renderer = GEngine->GetRenderer3D();
    renderer->MeshCreateFromComponent(this);
}

void SimpleMeshComponent::SetupVertexBuffer(Dg::BufferDesc* descriptor, Dg::BufferData* data)
{
    size_t vertexCount = 0;
    // TODO: Clean this up when the data goes out of scope
    std::vector<Vertex>* vertices = nullptr;

    if (shape == Cube)
    {
        vertices = new std::vector<Vertex>
        {
            // Front face (Z negative)
            {Dg::float3(-1,-1,-1), Dg::float3(0,0,-1), Dg::float2(0,1), Dg::float4(1,0,0,1)},
            {Dg::float3(-1,+1,-1), Dg::float3(0,0,-1), Dg::float2(0,0), Dg::float4(1,0,0,1)},
            {Dg::float3(+1,+1,-1), Dg::float3(0,0,-1), Dg::float2(1,0), Dg::float4(1,0,0,1)},
            {Dg::float3(+1,-1,-1), Dg::float3(0,0,-1), Dg::float2(1,1), Dg::float4(1,0,0,1)},

            // Back face (Z positive)
            {Dg::float3(-1,-1,+1), Dg::float3(0,0,1), Dg::float2(0,1), Dg::float4(0,1,0,1)},
            {Dg::float3(-1,+1,+1), Dg::float3(0,0,1), Dg::float2(0,0), Dg::float4(0,1,0,1)},
            {Dg::float3(+1,+1,+1), Dg::float3(0,0,1), Dg::float2(1,0), Dg::float4(0,1,0,1)},
            {Dg::float3(+1,-1,+1), Dg::float3(0,0,1), Dg::float2(1,1), Dg::float4(0,1,0,1)},

            // Left face (X negative)
            {Dg::float3(-1,-1,-1), Dg::float3(-1,0,0), Dg::float2(0,1), Dg::float4(0,0,1,1)},
            {Dg::float3(-1,+1,-1), Dg::float3(-1,0,0), Dg::float2(0,0), Dg::float4(0,0,1,1)},
            {Dg::float3(-1,+1,+1), Dg::float3(-1,0,0), Dg::float2(1,0), Dg::float4(0,0,1,1)},
            {Dg::float3(-1,-1,+1), Dg::float3(-1,0,0), Dg::float2(1,1), Dg::float4(0,0,1,1)},

            // Right face (X positive)
            {Dg::float3(+1,-1,-1), Dg::float3(1,0,0), Dg::float2(0,1), Dg::float4(1,1,0,1)},
            {Dg::float3(+1,+1,-1), Dg::float3(1,0,0), Dg::float2(0,0), Dg::float4(1,1,0,1)},
            {Dg::float3(+1,+1,+1), Dg::float3(1,0,0), Dg::float2(1,0), Dg::float4(1,1,0,1)},
            {Dg::float3(+1,-1,+1), Dg::float3(1,0,0), Dg::float2(1,1), Dg::float4(1,1,0,1)},

            // Top face (Y positive)
            {Dg::float3(-1,+1,-1), Dg::float3(0,1,0), Dg::float2(0,1), Dg::float4(1,0,1,1)},
            {Dg::float3(-1,+1,+1), Dg::float3(0,1,0), Dg::float2(0,0), Dg::float4(1,0,1,1)},
            {Dg::float3(+1,+1,+1), Dg::float3(0,1,0), Dg::float2(1,0), Dg::float4(1,0,1,1)},
            {Dg::float3(+1,+1,-1), Dg::float3(0,1,0), Dg::float2(1,1), Dg::float4(1,0,1,1)},

            // Bottom face (Y negative)
            {Dg::float3(-1,-1,-1), Dg::float3(0,-1,0), Dg::float2(0,1), Dg::float4(0,1,1,1)},
            {Dg::float3(-1,-1,+1), Dg::float3(0,-1,0), Dg::float2(0,0), Dg::float4(0,1,1,1)},
            {Dg::float3(+1,-1,+1), Dg::float3(0,-1,0), Dg::float2(1,0), Dg::float4(0,1,1,1)},
            {Dg::float3(+1,-1,-1), Dg::float3(0,-1,0), Dg::float2(1,1), Dg::float4(0,1,1,1)},
        };
        vertexCount = vertices->size();
    }
    else if (shape == Quad)
    {
        vertexCount = 4;
        vertices = new std::vector<Vertex>
        {
            // Creating a quad in the XZ plane (facing up along Y axis)
            // Position                  Normal              UV        Color
            {Dg::float3(-1, 0, -1), Dg::float3(0,1,0), Dg::float2(0,0), Dg::float4(1,0,0,1)},  // Bottom-left
            {Dg::float3(-1, 0, +1), Dg::float3(0,1,0), Dg::float2(0,1), Dg::float4(0,1,0,1)},  // Top-left
            {Dg::float3(+1, 0, +1), Dg::float3(0,1,0), Dg::float2(1,1), Dg::float4(0,0,1,1)},  // Top-right
            {Dg::float3(+1, 0, -1), Dg::float3(0,1,0), Dg::float2(1,0), Dg::float4(1,1,1,1)},  // Bottom-right
        };
    }

    // Create a vertex buffer that stores cube vertices
    descriptor->Name      = "SimpleMesh";
    descriptor->Usage     = Dg::USAGE_IMMUTABLE;
    descriptor->BindFlags = Dg::BIND_VERTEX_BUFFER;
    descriptor->Size      = vertexCount * sizeof(Vertex);
    
    data->pData    = vertices->data();
    data->DataSize = vertexCount * sizeof(Vertex);
}

uint32 SimpleMeshComponent::SetupIndexBuffer(Dg::BufferDesc* descriptor, Dg::BufferData* data)
{
    uint32 indexCount = 36;  // 12 triangles * 3 vertices per triangle
    std::vector<uint32>* indices = nullptr;

    if (shape == Cube)
    {
        indices = new std::vector<uint32>
        {
            // Front face
            0,  1,  2,
            0,  2,  3,

            // Back face
            4,  6,  5,
            4,  7,  6,

            // Left face
            8,  9,  10,
            8,  10, 11,

            // Right face
            12, 14, 13,
            12, 15, 14,

            // Top face
            16, 17, 18,
            16, 18, 19,

            // Bottom face
            20, 22, 21,
            20, 23, 22
        };
        indexCount = indices->size();
    }
    else if (shape == Quad)
    {
        indexCount = 6;  // 2 triangles * 3 vertices per triangle
        indices = new std::vector<uint32>
        {
            0, 1, 2,  // First triangle
            0, 2, 3   // Second triangle
        };
    }

    descriptor->Name      = "SimpleMesh";
    descriptor->Usage     = Dg::USAGE_IMMUTABLE;
    descriptor->BindFlags = Dg::BIND_INDEX_BUFFER;
    descriptor->Size      = indexCount * sizeof(uint32);

    data->pData    = indices->data();
    data->DataSize = indexCount * sizeof(uint32);

    return indexCount;  // returning number of triangles
}
