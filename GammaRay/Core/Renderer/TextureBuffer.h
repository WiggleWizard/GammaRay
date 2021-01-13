#pragma once


class TextureBuffer
{
public:
    virtual void Bind() const = 0;
    virtual void Unbind() const = 0;

    virtual RendererID GetRendererId() const = 0;

    virtual void BindRGBTexture(Size2i size) = 0;

    virtual ~TextureBuffer() {}

    static TextureBuffer* Create();
};
