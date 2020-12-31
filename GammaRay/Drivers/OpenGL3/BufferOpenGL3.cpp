#include "grpch.h"
#include "BufferOpenGL3.h"

#include <glad/glad.h>


void VertexBufferOpenGL3::Bind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, m_rendererId);
}

void VertexBufferOpenGL3::Unbind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

VertexBufferOpenGL3::VertexBufferOpenGL3(float* vertices, uint32_t size)
{
    glGenBuffers(1, &m_rendererId);
    glBindBuffer(GL_ARRAY_BUFFER, m_rendererId);
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

VertexBufferOpenGL3::~VertexBufferOpenGL3()
{
    glDeleteBuffers(1, &m_rendererId);
    m_rendererId = 0;
}

void IndexBufferOpenGL3::Bind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_rendererId);
}

void IndexBufferOpenGL3::Unbind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

IndexBufferOpenGL3::IndexBufferOpenGL3(uint32_t* indices, uint32_t count)
{
    glGenBuffers(1, &m_rendererId);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_rendererId);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), indices, GL_STATIC_DRAW);
    m_count = count;
}

IndexBufferOpenGL3::~IndexBufferOpenGL3()
{
    glDeleteBuffers(1, &m_rendererId);
    m_rendererId = 0;
}
