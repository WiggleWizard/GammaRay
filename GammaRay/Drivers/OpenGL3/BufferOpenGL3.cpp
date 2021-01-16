#include "grpch.h"
#include "BufferOpenGL3.h"

#include <glad/glad.h>


void VertexBufferOpenGL3::Bind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, m_rendererId);
}

void VertexBufferOpenGL3::Unbind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

VertexBufferOpenGL3::VertexBufferOpenGL3(float* vertices, uint32_t size)
{
    glGenBuffers(1, &m_rendererId);
    glBindBuffer(GL_ARRAY_BUFFER, m_rendererId);
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

VertexBufferOpenGL3::~VertexBufferOpenGL3()
{
    glDeleteBuffers(1, &m_rendererId);
    m_rendererId = 0;
}

void IndexBufferOpenGL3::Bind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_rendererId);
}

void IndexBufferOpenGL3::Unbind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

IndexBufferOpenGL3::IndexBufferOpenGL3(uint32_t* indices, uint32_t count)
{
    glGenBuffers(1, &m_rendererId);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_rendererId);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), indices, GL_STATIC_DRAW);
    m_count = count;
}

IndexBufferOpenGL3::~IndexBufferOpenGL3()
{
    glDeleteBuffers(1, &m_rendererId);
    m_rendererId = 0;
}

void FrameBufferOpenGL::Bind() const
{
    glBindFramebuffer(GL_FRAMEBUFFER, m_rendererId);
}

void FrameBufferOpenGL::Unbind() const
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void FrameBufferOpenGL::AttachRenderBuffer(RenderBuffer* renderBuffer, int attachmentType)
{
    m_attachedRenderBuffer = dynamic_cast<RenderBufferOpenGL*>(renderBuffer);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, attachmentType, GL_RENDERBUFFER, renderBuffer->GetRendererId());
}

void FrameBufferOpenGL::AttachTextureBuffer(TextureBuffer* textureBuffer, int attachmentLocation)
{
    int textureBufferOpenGLId = textureBuffer->GetRendererId();

    m_boundTextureBuffers[attachmentLocation] = dynamic_cast<TextureBufferOpenGL*>(textureBuffer);
    glFramebufferTexture2D(GL_FRAMEBUFFER, attachmentLocation, GL_TEXTURE_2D, textureBufferOpenGLId, 0);
}

FrameBufferOpenGL::FrameBufferOpenGL()
    : m_rendererId(0)
{
    glGenFramebuffers(1, &m_rendererId);
}

FrameBufferOpenGL::~FrameBufferOpenGL()
{
    glDeleteFramebuffers(1, &m_rendererId);
}

void RenderBufferOpenGL::Bind() const
{
    glBindRenderbuffer(GL_RENDERBUFFER, m_rendererId);
}

void RenderBufferOpenGL::Unbind() const
{
    glBindRenderbuffer(GL_RENDERBUFFER, 0);
}

void RenderBufferOpenGL::SetStorage(int mode, Size2i size)
{
    glRenderbufferStorage(GL_RENDERBUFFER, mode, size.x, size.y);
}

RenderBufferOpenGL::RenderBufferOpenGL()
    : m_rendererId(0)
{
    glGenRenderbuffers(1, &m_rendererId);
}

RenderBufferOpenGL::~RenderBufferOpenGL()
{
    glDeleteRenderbuffers(1, &m_rendererId);
}

void TextureBufferOpenGL::Bind() const
{
    glBindTexture(GL_TEXTURE_2D, m_rendererId);

    // TODO: Make these params
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void TextureBufferOpenGL::Unbind() const
{
    glBindTexture(GL_TEXTURE_2D, 0);
}

void TextureBufferOpenGL::BindRGBTexture(Size2i size, int format)
{
    glTexImage2D(GL_TEXTURE_2D, 0, format, size.x, size.y, 0, format, GL_UNSIGNED_BYTE, NULL);
}

inline RendererID TextureBufferOpenGL::GetRendererId() const
{
    return m_rendererId;
}

TextureBufferOpenGL::TextureBufferOpenGL()
{
    glGenTextures(1, &m_rendererId);
}

TextureBufferOpenGL::~TextureBufferOpenGL()
{
    glDeleteTextures(1, &m_rendererId);
}
