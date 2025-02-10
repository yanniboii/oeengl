#pragma once
#include "../Abstraction/LowAbstraction/Shader.h"

class Scene;

class Material {
public:
	Material(Shader* shader);
	Material(Shader* shader, glm::vec3 color);
	~Material();

	void Render(glm::mat4 model, glm::mat4 view, glm::mat4 projection, Scene* scene);

	glm::vec3 GetColor();
	void SetColor(glm::vec3 color);

	Shader* shader;
private:
	glm::vec3 color;
};