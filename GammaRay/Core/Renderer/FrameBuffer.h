#pragma once

#include "Core/Renderer/RenderBuffer.h"
#include "Core/Renderer/TextureBuffer.h"


class FrameBuffer
{
public:
    virtual void Bind() const = 0;
    virtual void Unbind() const = 0;

    virtual void AttachRenderBuffer(RenderBuffer* renderBuffer, int attachmentType) = 0;
    virtual void AttachTextureBuffer(TextureBuffer* textureBuffer, int attachmentLocation) = 0;

    virtual ~FrameBuffer() {}

    static FrameBuffer* Create();
};
