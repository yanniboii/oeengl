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
	GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
	if (status != GL_FRAMEBUFFER_COMPLETE) {
		switch (status) {
		case GL_FRAMEBUFFER_UNDEFINED:
			std::cerr << "Framebuffer error: GL_FRAMEBUFFER_UNDEFINED" << std::endl;
			break;
		case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT:
			std::cerr << "Framebuffer error: GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT" << std::endl;
			break;
		case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT:
			std::cerr << "Framebuffer error: GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT" << std::endl;
			break;
		case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER:
			std::cerr << "Framebuffer error: GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER" << std::endl;
			break;
		case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER:
			std::cerr << "Framebuffer error: GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER" << std::endl;
			break;
		case GL_FRAMEBUFFER_UNSUPPORTED:
			std::cerr << "Framebuffer error: GL_FRAMEBUFFER_UNSUPPORTED" << std::endl;
			break;
		case GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE:
			std::cerr << "Framebuffer error: GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE" << std::endl;
			break;
		case GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS:
			std::cerr << "Framebuffer error: GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS" << std::endl;
			break;
		default:
			std::cerr << "Framebuffer error: Unknown error" << std::endl;
		}
	}
	else {
		std::cout << "Framebuffer is complete." << std::endl;
	}
}