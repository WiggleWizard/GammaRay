#include "grpch.h"
#include "Buffer.h"

#include "Renderer.h"

#include "Drivers/OpenGL3/BufferOpenGL3.h"


VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size)
{
    switch(Renderer::GetRendererAPI())
    {
        case RendererAPI::None:   return nullptr; break;
        case RendererAPI::OpenGL: return new VertexBufferOpenGL3(vertices, size); break;
        default:                  return nullptr; break;
    }

    return nullptr;
}

IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t count)
{
    switch(Renderer::GetRendererAPI())
    {
        case RendererAPI::None:   return nullptr; break;
        case RendererAPI::OpenGL: return new IndexBufferOpenGL3(indices, count); break;
        default:                  return nullptr; break;
    }

    return nullptr;
}