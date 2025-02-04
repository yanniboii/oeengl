#include "Renderer.h"
#include "Application.h"


void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	shader.Use();
	va.Bind();
	ib.Bind();

	glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr);
}

void Renderer::Draw(GameObject& go) const
{

}


void Renderer::Draw(Mesh& mesh, const Shader& shader) const
{
	Draw(mesh.GetVertexArray(), mesh.GetIndexBuffer(), shader);
}

void Renderer::Draw(GameObject* go) const
{
	std::vector<RenderObject*> renderObjects = go->GetRenderObjects();
	// TODO: find a better place for this now it is called every time I draw 
	glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)RESOLUTION.x / RESOLUTION.y, 0.1f, 100.0f);

	for (int i = 0; i < renderObjects.size(); i++) {

		Draw(*renderObjects[i], go->GetTransform(), camera->GetViewMatrix(), projection);
	}
}

void Renderer::Draw(RenderObject& ro, glm::mat4 model, glm::mat4 view, glm::mat4 projection) const
{
	Material* mat = ro.GetMaterial();
	Mesh* mesh = ro.GetMesh();

	mat->Render(model, view, projection);
	Draw(*ro.GetMesh(), *mat->mShader);
}

void Renderer::Clear()
{
	glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::SetActiveCamera(Camera* camera)
{
	this->camera = camera;
}
