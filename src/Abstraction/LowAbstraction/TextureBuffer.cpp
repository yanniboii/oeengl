#include "TextureBuffer.h"
#include <GLFW/glfw3.h>

TextureBuffer::TextureBuffer(
	GLenum target,
	GLsizei width,
	GLsizei height,
	bool depth)

	:target(target),
	width(width),
	height(height)
{
	glGenTextures(1, &m_RendererID);
	glBindTexture(target, m_RendererID);

	if (depth)
	{
		glTexImage2D(target,
			0,
			GL_DEPTH_COMPONENT24,
			width,
			height,
			0,
			GL_DEPTH_COMPONENT,
			GL_UNSIGNED_BYTE,
			NULL);
		glTexParameteri(target, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(target, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	}
	else
	{

		glTexImage2D(target,
			0,
			GL_RGBA16F,
			width,
			height,
			0,
			GL_RGBA,
			GL_UNSIGNED_BYTE,
			NULL);
		glTexParameteri(target, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(target, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	}

	glTexParameteri(target, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(target, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
}

TextureBuffer::~TextureBuffer()
{
	glDeleteTextures(1, &m_RendererID);
}

void TextureBuffer::AttachToFrameBuffer(GLenum target, GLenum attachment)
{
	glFramebufferTexture2D(target, attachment, GL_TEXTURE_2D, m_RendererID, 0);
}

void TextureBuffer::Bind() const
{
	glBindTexture(target, m_RendererID);
}

void TextureBuffer::Unbind() const
{
	glBindTexture(target, 0);
}
