#pragma once
#include <GL/glew.h>

class FrameBuffer {
public:
	FrameBuffer(GLenum target);
	~FrameBuffer();

	void Bind() const;
	void Unbind() const;

	void CheckStatus();
private:
	GLuint m_RendererID;
	GLenum target;
};