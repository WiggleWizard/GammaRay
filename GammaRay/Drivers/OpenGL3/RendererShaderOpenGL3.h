#pragma once
#include "Core/Renderer/RendererShader.h"

#include <glad/glad.h>


static GLenum ShaderDataTypeToOpenGL(ShaderDataType type)
{
    switch(type)
    {
        case ShaderDataType::Int:    return GL_INT;
        case ShaderDataType::Int2:   return GL_INT;
        case ShaderDataType::Int3:   return GL_INT;
        case ShaderDataType::Int4:   return GL_INT;
        case ShaderDataType::Bool:   return GL_INT;
    }

    return GL_FLOAT;
}

class RendererShaderOpenGL3 : public RendererShader
{
public:
    virtual bool Compile() override;
    virtual void Bind() const override;
    virtual void Unbind() const override;

    virtual void setMat4(const std::string& name, const glm::mat4& mat) const override
    {
        glUniformMatrix4fv(glGetUniformLocation(m_vertexShaderId, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }

    virtual ~RendererShaderOpenGL3();
};

