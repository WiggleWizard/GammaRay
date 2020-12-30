#include "grpch.h"
#include "RendererShader.h"


RendererShader::RendererShader()
{
}

RendererShader::~RendererShader()
{
}

void RendererShader::Setup(const char* vertShaderSrc, const char* fragShaderSrc, const char* _, const char* shaderName)
{
    m_name = shaderName;
    m_vertexShaderSrc   = vertShaderSrc;
    m_fragmentShaderSrc = fragShaderSrc;
}
