#pragma once

#include <string>

#define INVALID_SHADER_ID 0

enum class ShaderDataType
{
    None = 0,
    Float, Float2, Float3, Float4,
    Mat3, Mat4,
    Int, Int2, Int3, Int4,
    Bool
};

static uint32_t ShaderDataTypeSize(ShaderDataType type)
{
    switch(type)
    {
        case ShaderDataType::Float:  return 4;
        case ShaderDataType::Float2: return 4 * 2;
        case ShaderDataType::Float3: return 4 * 3;
        case ShaderDataType::Float4: return 4 * 4;
        case ShaderDataType::Mat3:   return 4 * 3 * 3;
        case ShaderDataType::Mat4:   return 4 * 4 * 4;
        case ShaderDataType::Int:    return 4;
        case ShaderDataType::Int2:   return 4 * 2;
        case ShaderDataType::Int3:   return 4 * 3;
        case ShaderDataType::Int4:   return 4 * 4;
        case ShaderDataType::Bool:   return 1;
    }

    GR_CORE_ASSERT(false, "Shader data size could not be determined from type");
    return 0;
}

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

