#include "Renderer.h"

void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	shader.Use();
	va.Bind();
	ib.Bind();

	glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr);
}


void Renderer::Draw(Mesh& mesh, const Shader& shader) const
{
	Draw(mesh.GetVertexArray(), mesh.GetIndexBuffer(), shader);
}

void Renderer::Draw(const GameObject& go) const
{

}
void Renderer::Draw(const RenderObject& ro) const
{

	//Draw();
}

void Renderer::Clear()
{
	glClear(GL_COLOR_BUFFER_BIT);
}
