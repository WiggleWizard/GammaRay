#pragma once

#include "StaticMeshComponent.h"

#include <BasicMath.hpp>

class SimpleMeshComponent : public StaticMeshComponent
{
public:
    enum Shape
    {
        Cube, Quad
    };

public:
    SimpleMeshComponent();

    void GenerateMesh(const Shape shape);

    void SetupVertexBuffer(Dg::BufferDesc* descriptor, Dg::BufferData* data) override;
    uint32 SetupIndexBuffer(Dg::BufferDesc* descriptor, Dg::BufferData* data) override;

    Shape shape = Shape::Cube;
};
