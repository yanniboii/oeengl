#pragma once
#include <GL/glew.h>

class TextureBuffer {
public:
	TextureBuffer(GLenum target,GLsizei width, GLsizei height);
	~TextureBuffer();

	void AttachToFrameBuffer(GLenum target);

	void Bind() const;
	void Unbind() const;
private:
	GLuint m_RendererID;
	GLenum target;
	GLsizei width;
	GLsizei height;
};