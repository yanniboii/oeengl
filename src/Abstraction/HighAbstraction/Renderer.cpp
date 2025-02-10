#include "Renderer.h"
#include "../../Application.h"
// TODO: this is a cyclical reference clean up some day 

void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	shader.Use();
	va.Bind();
	ib.Bind();

	glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr);
}

void Renderer::Draw(Scene* scene) const
{
	if (scene->ChildCount() <= 0)
		return;

	std::vector<GameObject*> children = scene->GetChildren();

	for (int i = 0; i < children.size(); i++)
	{
		if (children[i]->ChildCount() > 0)
			Draw(scene, children[i], true);
		else
			Draw(scene, children[i]);
	}
}


void Renderer::Draw(Mesh& mesh, const Shader& shader) const
{
	Draw(mesh.GetVertexArray(), mesh.GetIndexBuffer(), shader);
}

void Renderer::Draw(Scene* scene, GameObject* go, bool recursive) const
{
	// TODO: find a better place for this now it is called every time I draw 
	glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)RESOLUTION.x / RESOLUTION.y, 0.1f, 100.0f);

	std::vector<RenderObject*> renderObjects = go->GetRenderObjects();

	for (int i = 0; i < renderObjects.size(); i++) {

		Draw(scene, *renderObjects[i], go->GetTransform(), camera->GetViewMatrix(), projection);
	}

	if (!recursive)
		return;

	std::vector<GameObject*> children = go->GetChildren();

	for (int i = 0; i < children.size(); i++)
	{
		if (children[i]->ChildCount() > 0)
			Draw(scene, children[i], true);
		else
			Draw(scene, children[i]);
	}
}

void Renderer::Draw(Scene* scene, RenderObject& ro, glm::mat4 model, glm::mat4 view, glm::mat4 projection) const
{
	Material* mat = ro.GetMaterial();
	Mesh* mesh = ro.GetMesh();

	mat->Render(model, view, projection, scene);
	Draw(*ro.GetMesh(), *mat->shader);
}

void Renderer::Clear()
{
	glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::SetActiveCamera(Camera* camera)
{
	this->camera = camera;
}
