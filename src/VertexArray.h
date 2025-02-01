#pragma once
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include <GLFW/glfw3.h>
#include <vector>

class VertexArray {
public:
	VertexArray();
	~VertexArray();

	void Bind() const;
	void Unbind() const;

	void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);
private:
	unsigned int m_RendererID;
};