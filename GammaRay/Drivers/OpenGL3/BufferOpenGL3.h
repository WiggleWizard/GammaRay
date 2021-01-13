#pragma once

#include "Core/Renderer/Buffer.h"
#include "Core/Renderer/FrameBuffer.h"
#include "Core/Renderer/RenderBuffer.h"
#include "Core/Renderer/TextureBuffer.h"

#include "Core/Math/Rect.h"


class VertexBufferOpenGL3 : public VertexBuffer
{
public:
    virtual void Bind() const override;
    virtual void Unbind() const override;

    virtual const BufferLayout& GetLayout() const override { return m_layout; }
    virtual void SetLayout(const BufferLayout& layout) override { m_layout = layout; }

    VertexBufferOpenGL3(float* vertices, uint32_t size);
    ~VertexBufferOpenGL3();

private:
    RendererID m_rendererId = 0;
    BufferLayout m_layout;
};

class IndexBufferOpenGL3 : public IndexBuffer
{
public:
    virtual void Bind() const override;
    virtual void Unbind() const override;

    virtual uint32_t GetCount() const { return m_count; }

    IndexBufferOpenGL3(uint32_t* indices, uint32_t count);
    ~IndexBufferOpenGL3();

private:
    RendererID m_rendererId = 0;
    uint32_t m_count = 0;
};

class RenderBufferOpenGL : public RenderBuffer
{
public:
    virtual void Bind() const override;
    virtual void Unbind() const override;

    virtual void SetStorage(int mode, Size2i size);

    virtual RendererID GetRendererId() const { return m_rendererId; }

    RenderBufferOpenGL();
    virtual ~RenderBufferOpenGL();

private:
    RendererID m_rendererId = 0;
};

class FrameBufferOpenGL : public FrameBuffer
{
public:
    virtual void Bind() const override;
    virtual void Unbind() const override;

    virtual void AttachRenderBuffer(RenderBuffer* renderBuffer, int attachmentType) override;
    virtual void AttachTextureBuffer(TextureBuffer* textureBuffer, int attachmentLocation) override;

    FrameBufferOpenGL();
    ~FrameBufferOpenGL();

private:
    RendererID m_rendererId = 0;
    // TODO: Ideally this would be a pointer/Ref to a render buffer but for now
    //       renderbuffer contains just an int so it's ok to copy here.
    RenderBufferOpenGL* m_attachedRenderBuffer;
    std::vector<class TextureBufferOpenGL*> m_boundTextureBuffers;
};

class TextureBufferOpenGL : public TextureBuffer
{
public:
    virtual void Bind() const override;
    virtual void Unbind() const override;

    virtual void BindRGBTexture(Size2i size);

    RendererID GetRendererId() const { return m_rendererId; }

    TextureBufferOpenGL();
    ~TextureBufferOpenGL();

private:
    RendererID m_rendererId;
};
