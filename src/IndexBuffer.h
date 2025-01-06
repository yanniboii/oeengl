#pragma once
#include <GL/glew.h>

class IndexBuffer {
public:
	IndexBuffer(const unsigned int* data, unsigned int count);

	IndexBuffer();
	~IndexBuffer();

	void Bind() const;
	void Unbind() const;

	inline GLuint GetCount() const { return m_Count; };
	inline GLuint GetID() const { return m_RendererID; };
private:
	GLuint m_RendererID;
	GLuint m_Count;
};