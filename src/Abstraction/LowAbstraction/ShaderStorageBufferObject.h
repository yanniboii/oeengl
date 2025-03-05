#pragma once
#include "../Abstraction/HighAbstraction/Light.h"

class ShaderStorageBufferObject {
public:
	ShaderStorageBufferObject();
	~ShaderStorageBufferObject();

	void Bind() const;
	void Unbind() const;

	void SetBufferData(GLuint loc, GLsizeiptr size, const void* data);
	void AddBufferData(GLsizeiptr size, const void* data);
private:
	unsigned int m_RendererID;
};