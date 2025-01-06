#include "RenderBuffer.h"

RenderBuffer::RenderBuffer(GLsizei width, GLsizei height)
    :width(width), height(height)
{
    glGenRenderbuffers(1, &m_RendererID);
    glBindRenderbuffer(GL_RENDERBUFFER, m_RendererID);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
}

RenderBuffer::~RenderBuffer()
{
    glDeleteRenderbuffers(1,&m_RendererID);
}

void RenderBuffer::AttachToFrameBuffer(GLenum target)
{
    glFramebufferRenderbuffer(target, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_RendererID);
}

void RenderBuffer::Bind() const
{
    glBindRenderbuffer(GL_RENDERBUFFER, m_RendererID);
}
 
void RenderBuffer::Unbind() const 
{
    glBindRenderbuffer(GL_RENDERBUFFER, 0);
}
