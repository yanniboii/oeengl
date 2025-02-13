#pragma once
#include "../Abstraction/LowAbstraction/Shader.h"

class Scene;

class Material {
public:
	Material(Shader* shader);
	Material(Shader* shader, glm::vec4 color);
	~Material();

	void Render(glm::mat4 model, glm::mat4 view, glm::mat4 projection, Scene* scene);

	glm::vec4 GetColor();
	void SetColor(glm::vec4 color);

	Shader* shader;
private:
	glm::vec4 ambientColor;
	glm::vec4 diffuseColor;
	glm::vec4 specularColor;

	float ambientCoefficient;
	float diffuseCoefficient;
	float specularCoefficient;

	float specularShininess;
};