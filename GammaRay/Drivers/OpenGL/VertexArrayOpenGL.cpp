#include "grpch.h"
#include "VertexArrayOpenGL.h"

#include "Drivers/OpenGL/RendererShaderOpenGL.h"

#include <glad/glad.h>


void VertexArrayOpenGL::Bind() const
{
    glBindVertexArray(m_rendererId);
}

void VertexArrayOpenGL::Unbind() const
{
    glBindVertexArray(0);
}

void VertexArrayOpenGL::AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer)
{
    GR_CORE_ASSERT(vertexBuffer->GetLayout().GetElements().size(), "Vertex buffer has no layout");

    glBindVertexArray(m_rendererId);
    vertexBuffer->Bind();

    uint32_t index = 0;
    const auto& layout = vertexBuffer->GetLayout();
    for(const auto& element : layout)
    {
        glEnableVertexAttribArray(index);
        glVertexAttribPointer(
            index,
            element.GetComponentCount(),
            ShaderDataTypeToOpenGL(element.type),
            element.normalized ? GL_TRUE : GL_FALSE,
            layout.GetStride(),
            (const void*)element.offset);

        index++;
    }

    m_vertexBuffers.push_back(vertexBuffer);
}

void VertexArrayOpenGL::AddIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer)
{
    glBindVertexArray(m_rendererId);
    indexBuffer->Bind();

    m_indexBuffers.push_back(indexBuffer);
}

VertexArrayOpenGL::VertexArrayOpenGL()
{
    glGenVertexArrays(1, &m_rendererId);
}
