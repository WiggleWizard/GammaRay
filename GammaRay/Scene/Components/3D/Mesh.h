#pragma once

#include <memory>

class VertexBuffer;
class IndexBuffer;
class VertexArray;


struct ComponentMesh3D
{
    std::shared_ptr<VertexBuffer> vertices    = nullptr;
    std::shared_ptr<IndexBuffer>  indices     = nullptr;
    std::shared_ptr<VertexArray>  vertexArray = nullptr;
};
