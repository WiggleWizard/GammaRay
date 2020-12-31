#pragma once


enum class RendererAPI
{
    None = 0, OpenGL = 1
};

class Renderer
{
public:
    _FORCE_INLINE_ static RendererAPI GetRendererAPI() { return m_rendererAPI; }

private:
    static RendererAPI m_rendererAPI;
};
