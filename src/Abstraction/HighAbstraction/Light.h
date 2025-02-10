#pragma once
#include "GameObject.h"

class Light : public GameObject {
public:
	Light() : lightColor(glm::vec3(1, 1, 1)) {};
	~Light() {};

	void SetLightColor(glm::vec3 lightColor) { this->lightColor = lightColor; };
	glm::vec3 GetLightColor() { return lightColor; };

private:
	glm::vec3 lightColor;
};