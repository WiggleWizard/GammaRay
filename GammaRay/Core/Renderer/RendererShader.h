#pragma once

#include <string>
#include "ShaderVariable.h"

#define INVALID_SHADER_ID 0



class RendererShader : public Object
{
public:
    RendererShader();
    virtual ~RendererShader();

    void Setup(const char* vertShaderSrc, const char* fragShaderSrc, const char* _, const char* shaderName);
    void LoadFromFile(const std::string& filePath);

    virtual bool Compile() = 0;
    virtual void Bind() const = 0;
    virtual void Unbind() const = 0;

protected:
    std::string m_name = "";
    std::string m_vertexShaderSrc;
    std::string m_fragmentShaderSrc;

    uint32_t m_vertexShaderId = 0;
    uint32_t m_fragmentShaderId = 0;

    uint32_t m_rendererId = INVALID_SHADER_ID;
};

