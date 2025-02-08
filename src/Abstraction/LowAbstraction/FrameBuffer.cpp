#include "FrameBuffer.h"
#include <iostream>

FrameBuffer::FrameBuffer(GLenum target) 
    :target(target)
{
    glGenFramebuffers(1, &m_RendererID);
    glBindFramebuffer(this->target, m_RendererID);
}

FrameBuffer::~FrameBuffer()
{
    glDeleteFramebuffers(1, &m_RendererID);
}

void FrameBuffer::Bind() const
{
    glBindFramebuffer(target, m_RendererID);
}

void FrameBuffer::Unbind() const
{
    glBindFramebuffer(target, 0);
}

void FrameBuffer::CheckStatus()
{
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE)
        std::cout << "FRAMEBUFFER COMPLETE" << std::endl;
}
