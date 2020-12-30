#pragma once

#include <string>


class RendererShader : public Object
{
public:
    RendererShader();
    virtual ~RendererShader();

    void Setup(const char* vertShaderSrc, const char* fragShaderSrc, const char* _, const char* shaderName);

    virtual bool Compile() = 0;
    virtual void Bind() const = 0;
    virtual void Unbind() const = 0;

protected:
    std::string m_name = "";
    const char* m_vertexShaderSrc = nullptr;
    const char* m_fragmentShaderSrc = nullptr;

    uint32_t m_rendererId = 0;
};

