#pragma once

#include "ShaderVariable.h"

#include <string>
#include <glm/glm.hpp>

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

    virtual uint32_t GetRendererId() { return m_rendererId; }

    virtual int GetUniformLoc(const std::string& name) const = 0;

    virtual void SetMat4(const std::string& name, const glm::mat4& mat) const = 0;
    virtual void SetMat4(int uniformLoc, const glm::mat4& mat) const = 0;

protected:
    std::string m_name = "";
    std::string m_vertexShaderSrc;
    std::string m_fragmentShaderSrc;

    uint32_t m_vertexShaderId = 0;
    uint32_t m_fragmentShaderId = 0;

    uint32_t m_rendererId = INVALID_SHADER_ID;
};

