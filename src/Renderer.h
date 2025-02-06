#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Scene.h"
#include "Camera.h"


class Renderer {
public:
	void Draw(const VertexArray& va, const IndexBuffer& ib, const  Shader& shader) const;
	void Draw(Scene* scene) const;
	void Draw(GameObject* go, bool recursive = false) const;
	void Draw(RenderObject& ro, glm::mat4 model, glm::mat4 view, glm::mat4 projection) const;
	void Draw(Mesh& mesh, const Shader& shader) const;
	void Clear();

	void SetActiveCamera(Camera* camera);
private:
	Camera* camera;
};