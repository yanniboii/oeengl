#pragma once
#include <GL/glew.h>

class VertexBuffer {
public:
	VertexBuffer(unsigned int size, const void* data);
	VertexBuffer();
	~VertexBuffer();

	void AddData(unsigned int size, const void* data);
	void Bind() const;
	void Unbind() const;

private:
	GLuint m_RendererID;
};