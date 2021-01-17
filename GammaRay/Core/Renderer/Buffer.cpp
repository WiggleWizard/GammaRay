#include "grpch.h"
#include "Buffer.h"

#include "FrameBuffer.h"
#include "TextureBuffer.h"

#include "Renderer.h"

#include "Drivers/OpenGL/BufferOpenGL.h"


VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size)
{
    switch(Renderer::GetRendererAPI())
    {
        case RendererAPI::None:   return nullptr; break;
        case RendererAPI::OpenGL: return new VertexBufferOpenGL(vertices, size); break;
        default:                  return nullptr; break;
    }

    return nullptr;
}

IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t count)
{
    switch(Renderer::GetRendererAPI())
    {
        case RendererAPI::None:   return nullptr; break;
        case RendererAPI::OpenGL: return new IndexBufferOpenGL(indices, count); break;
        default:                  return nullptr; break;
    }

    return nullptr;
}

FrameBuffer* FrameBuffer::Create()
{
    switch(Renderer::GetRendererAPI())
    {
    case RendererAPI::None:   return nullptr; break;
    case RendererAPI::OpenGL: return new FrameBufferOpenGL(); break;
    default:                  return nullptr; break;
    }

    return nullptr;
}

RenderBuffer* RenderBuffer::Create()
{
    switch(Renderer::GetRendererAPI())
    {
    case RendererAPI::None:   return nullptr; break;
    case RendererAPI::OpenGL: return new RenderBufferOpenGL(); break;
    default:                  return nullptr; break;
    }

    return nullptr;
}

TextureBuffer* TextureBuffer::Create()
{
    switch(Renderer::GetRendererAPI())
    {
    case RendererAPI::None:   return nullptr; break;
    case RendererAPI::OpenGL: return new TextureBufferOpenGL(); break;
    default:                  return nullptr; break;
    }

    return nullptr;
}
