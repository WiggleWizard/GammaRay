/**
 * Abstracts away from VAOs.
 */

#pragma once

#include "Core/Renderer/VertexArray.h"

#include <vector>


class VertexArrayOpenGL : public VertexArray
{
   
public:
    virtual void Bind() const override;
    virtual void Unbind() const override;

    virtual void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) override;
    virtual void AddIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer) override;

    virtual const std::vector<std::shared_ptr<VertexBuffer>>& GetVertexBuffers() const { return m_vertexBuffers; }
    virtual const std::vector<std::shared_ptr<IndexBuffer>>& GetIndexBuffers() const { return m_indexBuffers; }

    VertexArrayOpenGL();

private:
    uint32_t m_rendererId;
    std::vector<std::shared_ptr<VertexBuffer>> m_vertexBuffers;
    std::vector<std::shared_ptr<IndexBuffer>> m_indexBuffers;
};

