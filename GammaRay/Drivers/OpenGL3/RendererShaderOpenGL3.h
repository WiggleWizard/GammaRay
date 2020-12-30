#pragma once
#include "Core/Renderer/RendererShader.h"


class RendererShaderOpenGL3 : public RendererShader
{
public:
    virtual bool Compile() override;
    virtual void Bind() const override;
    virtual void Unbind() const override;

    virtual ~RendererShaderOpenGL3();
};

