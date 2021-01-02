#pragma once

#include "Core/Renderer/Buffer.h"
#include "Core/Renderer/VertexArray.h"
#include "Core/Renderer/RendererShader.h"


class RenderServer
{
public:
    static RenderServer* GetSingleton() { return m_singleton; }

    void OnUpdate();
    unsigned int GetDrawCallCount() { return m_drawCallsThisFrame; }

    RenderServer();

private:
    static RenderServer* m_singleton;

    unsigned int m_drawCallsThisFrame = 0;

    std::unique_ptr<RendererShader> m_shader;
};

