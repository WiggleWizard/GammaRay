#pragma once

#include "Component.h"

class StaticMeshComponent : public Component
{
public:
    StaticMeshComponent() = default;

    UUID rendererMeshID;
    
    virtual void SetupVertexBuffer(Dg::BufferDesc* descriptor, Dg::BufferData* data) {}
    virtual uint32 SetupIndexBuffer(Dg::BufferDesc* descriptor, Dg::BufferData* data) { return 0; }
};