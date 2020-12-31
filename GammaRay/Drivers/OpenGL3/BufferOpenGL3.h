#pragma once
#include "Core/Renderer/Buffer.h"


class VertexBufferOpenGL3 : public VertexBuffer
{
public:
    virtual void Bind() const override;
    virtual void Unbind() const override;

    VertexBufferOpenGL3(float* vertices, uint32_t size);
    ~VertexBufferOpenGL3();

private:
    RendererID m_rendererId = 0;
};

class IndexBufferOpenGL3 : public IndexBuffer
{
public:
    virtual void Bind() const override;
    virtual void Unbind() const override;

    virtual uint32_t GetCount() const { return m_count; }

    IndexBufferOpenGL3(uint32_t* indices, uint32_t count);
    ~IndexBufferOpenGL3();

private:
    RendererID m_rendererId = 0;
    uint32_t m_count = 0;
};

