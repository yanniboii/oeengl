#include "ShaderStorageBufferObject.h"

ShaderStorageBufferObject::ShaderStorageBufferObject()
{
	glGenBuffers(1, &m_RendererID);
}

ShaderStorageBufferObject::~ShaderStorageBufferObject()
{
	glDeleteBuffers(1, &m_RendererID);
}

void ShaderStorageBufferObject::Bind() const
{
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, m_RendererID);
}

void ShaderStorageBufferObject::Unbind() const
{
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
}

void ShaderStorageBufferObject::SetBufferData(GLuint loc, GLsizeiptr size, const void* data)
{
	Bind();
	glBindBufferBase(GL_SHADER_STORAGE_BUFFER, loc, m_RendererID);
	glBufferData(
		GL_SHADER_STORAGE_BUFFER,
		size,
		data,
		GL_DYNAMIC_DRAW);
}

void ShaderStorageBufferObject::AddBufferData(GLsizeiptr size, const void* data)
{
	Bind();
	glBufferData(
		GL_SHADER_STORAGE_BUFFER,
		size,
		data,
		GL_DYNAMIC_DRAW);
}
