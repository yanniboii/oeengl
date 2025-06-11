#pragma once
#include <GL/glew.h>

class TextureBuffer {
public:
	TextureBuffer(
		GLenum target,
		GLsizei width,
		GLsizei height,
		bool depth = false);
	~TextureBuffer();

	void AttachToFrameBuffer(GLenum target, GLenum attachment = GL_COLOR_ATTACHMENT0);

	void Bind() const;
	void Bind(GLenum attachment) const;
	void Unbind() const;
private:
	GLuint m_RendererID;
	GLenum target;
	GLsizei width;
	GLsizei height;
};