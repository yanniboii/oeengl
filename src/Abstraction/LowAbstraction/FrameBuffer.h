#pragma once
#include <GL/glew.h>
#include <string>
class FrameBuffer {
public:
	FrameBuffer(GLenum target, std::string name = "empty");
	~FrameBuffer();

	void Bind() const;
	void Unbind() const;

	void CheckStatus();
	std::string name;
private:
	GLuint m_RendererID;
	GLenum target;
};