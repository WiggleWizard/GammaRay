#pragma once

#include "Core/Renderer/Buffer.h"
#include "Core/Renderer/VertexArray.h"
#include "Core/Renderer/RendererShader.h"


class RenderServer
{
public:
    static RenderServer* GetSingleton() { return m_singleton; }

    void OnUpdate();

    RenderServer();

private:
    static RenderServer* m_singleton;


    std::shared_ptr<VertexArray> m_vertexArray;
    std::shared_ptr<VertexBuffer> m_vertexBuffer;
    std::shared_ptr<IndexBuffer> m_indexBuffer;

    std::shared_ptr<VertexArray> m_squareVA;

    unsigned int vertexArray, vertexBuffer, vertexIndex;
    std::unique_ptr<RendererShader> m_shader;
};

