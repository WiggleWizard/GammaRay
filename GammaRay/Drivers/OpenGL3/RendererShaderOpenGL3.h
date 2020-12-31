#pragma once
#include "Core/Renderer/RendererShader.h"

#include <glad/glad.h>


static GLenum ShaderDataTypeToOpenGL(ShaderDataType type)
{
    switch(type)
    {
        case ShaderDataType::Float:  return GL_FLOAT;
        case ShaderDataType::Float2: return GL_FLOAT;
        case ShaderDataType::Float3: return GL_FLOAT;
        case ShaderDataType::Float4: return GL_FLOAT;
        case ShaderDataType::Mat3:   return GL_FLOAT;
        case ShaderDataType::Mat4:   return GL_FLOAT;
        case ShaderDataType::Int:    return GL_INT;
        case ShaderDataType::Int2:   return GL_INT;
        case ShaderDataType::Int3:   return GL_INT;
        case ShaderDataType::Int4:   return GL_INT;
        case ShaderDataType::Bool:   return GL_INT;
    }
}

class RendererShaderOpenGL3 : public RendererShader
{
public:
    virtual bool Compile() override;
    virtual void Bind() const override;
    virtual void Unbind() const override;

    virtual ~RendererShaderOpenGL3();
};

