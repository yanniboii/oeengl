#pragma once
#include "Shader.h"
#include <glm/glm.hpp>

class Material {
public:
	Shader Shader;

	glm::vec4 GetColor();
	void SetColor(glm::vec4 color);
private:
	glm::vec4 color;
};