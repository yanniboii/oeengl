#pragma once
#include "../Abstraction/LowAbstraction/Shader.h"

class Material {
public:
	Material(Shader* shader);
	~Material();

	void Render(glm::mat4 model, glm::mat4 view, glm::mat4 projection);

	glm::vec4 GetColor();
	void SetColor(glm::vec4 color);

	Shader* mShader;
private:
	glm::vec4 color;
};