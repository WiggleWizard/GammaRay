#pragma once

#include "Core/Object/Component.h"

#include <memory>

class VertexBuffer;
class IndexBuffer;
class VertexArray;


struct ComponentMesh3D : public Component
{
    std::shared_ptr<VertexBuffer> vertices    = nullptr;
    std::shared_ptr<IndexBuffer>  indices     = nullptr;
    std::shared_ptr<VertexArray>  vertexArray = nullptr;
};
