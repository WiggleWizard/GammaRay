#pragma once


class VertexBuffer
{
public:
    virtual void Bind() const = 0;
    virtual void Unbind() const = 0;

    virtual ~VertexBuffer() {}

    static VertexBuffer* Create(float* vertices, uint32_t size);
};

class IndexBuffer
{
public:
    virtual void Bind() const = 0;
    virtual void Unbind() const = 0;

    virtual uint32_t GetCount() const = 0;

    virtual ~IndexBuffer() {}

    static IndexBuffer* Create(uint32_t* indices, uint32_t size);
};
