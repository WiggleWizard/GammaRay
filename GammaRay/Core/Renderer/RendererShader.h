#pragma once

#include <string>


class RendererShader
{
public:
    RendererShader(const std::string& vertexSrc, const std::string& fragmentSrc);
    ~RendererShader();

    void Bind() const;
    void Unbind() const;

private:
    uint32_t m_rendererId = 0;
};

