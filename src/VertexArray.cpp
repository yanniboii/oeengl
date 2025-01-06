#include "VertexArray.h"

VertexArray::VertexArray()
{
	glGenVertexArrays(1, &m_RendererID);
}

VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &m_RendererID);
}

void VertexArray::Bind() const
{
	glBindVertexArray(m_RendererID);
}

void VertexArray::Unbind() const
{
	glBindVertexArray(0);
}

void VertexArray::AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout)
{
	Bind();
	vb.Bind();
	const auto& elements = layout.GetElements();
	unsigned int offset = 0;
	for (int i = 0; i < elements.size(); i++) {
		const auto& element = elements[i];
		glEnableVertexAttribArray(i);

		glVertexAttribPointer(
			i, 
			element.count, 
			element.type, 
			element.normalized, 
			layout.GetStride(), 
			(const void*)offset);

		offset += element.count * VertexBufferElement::GetSizeOfType(element.type);
	}

}
void VertexArray::AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout, const bool isVertex)
{
	Bind();
	vb.Bind();
	const auto& elements = layout.GetElements();
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(
			0,
			elements[0].count,
			elements[0].type,
			elements[0].normalized,
			sizeof(Vertex),
			(const void*)0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(
			1,
			elements[1].count,
			elements[1].type,
			elements[1].normalized,
			sizeof(Vertex),
			(const void*)offsetof(Vertex, colors));		
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(
			2,
			elements[2].count,
			elements[2].type,
			elements[2].normalized,
			sizeof(Vertex),
			(const void*)offsetof(Vertex, normals));
		glEnableVertexAttribArray(3);
		glVertexAttribPointer(
			3,
			elements[3].count,
			elements[3].type,
			elements[3].normalized,
			sizeof(Vertex),
			(const void*)offsetof(Vertex, uvs));
}