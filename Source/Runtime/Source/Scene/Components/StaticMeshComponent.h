#pragma once

#include "Component.h"

class StaticMeshComponent : public Component
{
public:
    StaticMeshComponent() = default;

    UUID rendererMeshID;
    
    virtual void SetupVertexBuffer(Dg::BufferDesc* descriptor, Dg::BufferData* data) {}
    virtual void SetupIndexBuffer(Dg::BufferDesc* descriptor, Dg::BufferData* data) {}
};