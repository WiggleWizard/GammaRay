#include "grpch.h"
#include "VertexArray.h"

#include "Core/Renderer/Renderer.h"
#include "Drivers/OpenGL3/VertexArrayOpenGL.h"


VertexArray* VertexArray::Create()
{
    switch(Renderer::GetRendererAPI())
    {
        case RendererAPI::None:   return nullptr;
        case RendererAPI::OpenGL: return new VertexArrayOpenGL();
        default:                  return nullptr;
    }

    return nullptr;
}
