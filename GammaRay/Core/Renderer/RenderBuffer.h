#pragma once

#include "Core/Math/Vector2.h"


class RenderBuffer
{
public:
    virtual void Bind() const = 0;
    virtual void Unbind() const = 0;

    virtual RendererID GetRendererId() const = 0;

    virtual void SetStorage(int mode, Size2i size) = 0;

    virtual ~RenderBuffer() {}

    static RenderBuffer* Create();
};
