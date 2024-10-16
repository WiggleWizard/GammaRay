#pragma once

#include "StaticMeshComponent.h"

#include <BasicMath.hpp>

class SimpleMeshComponent : public StaticMeshComponent
{
public:
    SimpleMeshComponent();

    void GenerateMesh();

    void SetupVertexBuffer(Dg::BufferDesc* descriptor, Dg::BufferData* data) override;
    void SetupIndexBuffer(Dg::BufferDesc* descriptor, Dg::BufferData* data) override;
};
