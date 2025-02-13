#pragma once
#include "GameObject.h"

struct LightData {
	glm::vec4 ambientColor = glm::vec4(1, 1, 1, 1);
	glm::vec4 diffuseColor = glm::vec4(1, 1, 0, 1);
	glm::vec4 specularColor = glm::vec4(1, 0, 1, 1);

	float ambientIntensity = 0.5f;
	float diffuseIntensity = 0.5f;
	float specularIntensity = 0.5f;

	float constant = 1;
	float linear = 0.5f;
	float quadratic = 0.1f;
};

class Light : public GameObject {
public:
	Light() {};
	~Light() {};

	void SetLightData(LightData& data) { lightData = data; };

	void SetAmbientColor(glm::vec4& col) { lightData.ambientColor = col; };
	void SetDiffuseColor(glm::vec4& col) { lightData.diffuseColor = col; };
	void SetSpecularColor(glm::vec4& col) { lightData.specularColor = col; };

	void SetAmbientIntensity(float intensity) { lightData.ambientIntensity = intensity; };
	void SetDiffuseIntensity(float intensity) { lightData.diffuseIntensity = intensity; };
	void SetSpecularIntensity(float intensity) { lightData.specularIntensity = intensity; };

	void SetConstantAttenuation(float intensity) { lightData.constant = intensity; };
	void SetLinearAttenuation(float intensity) { lightData.linear = intensity; };
	void SetQuadraticAttenuation(float intensity) { lightData.quadratic = intensity; };

	LightData GetLightData() { return lightData; };

private:
	LightData lightData;
};