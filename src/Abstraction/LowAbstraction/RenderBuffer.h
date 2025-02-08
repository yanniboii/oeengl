#pragma once
#include <GL/glew.h>

class RenderBuffer {
	public:
		RenderBuffer(GLsizei width, GLsizei height);
		~RenderBuffer();

		void AttachToFrameBuffer(GLenum target);

		void Bind() const;
		void Unbind() const;
private:
	GLuint m_RendererID;
	GLsizei width;
	GLsizei height;
};