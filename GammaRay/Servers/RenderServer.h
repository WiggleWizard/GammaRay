#pragma once

#include "Core/Timestep.h"
#include "Core/Renderer/Buffer.h"
#include "Core/Renderer/FrameBuffer.h"
#include "Core/Renderer/RenderBuffer.h"
#include "Core/Renderer/TextureBuffer.h"
#include "Core/Renderer/VertexArray.h"
#include "Core/Renderer/RendererShader.h"


class RenderServer
{
public:
    static RenderServer* GetSingleton() { return m_singleton; }

    void OnUpdate();
    unsigned int GetDrawCallCount() { return m_drawCallsThisFrame; }
    const Timestep& GetFrameTime() const { return m_frameTime; }

    RenderServer();
    ~RenderServer();

    std::unique_ptr<TextureBuffer> m_texDepth;

private:
    static RenderServer* m_singleton;

    unsigned int m_drawCallsThisFrame = 0;
    Timestep m_frameTime = 0.f;
    float m_lastFrameTime = 0.f;

    std::unique_ptr<RendererShader> m_shader;
    std::unique_ptr<RendererShader> m_shaderDepth;

    std::unique_ptr<FrameBuffer> m_fboDepth;
    std::unique_ptr<RenderBuffer> m_rboDepth;

    //unsigned int m_fboDepth;
};

