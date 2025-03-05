#pragma once
#include "GameObject.h"

struct LightData {
	glm::vec4 ambientColor = glm::vec4(1, 1, 1, 1);
	glm::vec4 diffuseColor = glm::vec4(0, 1, 0, 1);
	glm::vec4 specularColor = glm::vec4(1, 0, 0, 1);

	glm::vec3 lightPos = glm::vec3(0, 1, 0);

	float ambientIntensity = 0.5f;
	float diffuseIntensity = 10.0f;
	float specularIntensity = 0.2f;

	float constant = 1;
	float linear = 0.9f;
	float quadratic = 0.032f;

	float innerCutoff = 0.2f;
	float outerCutoff = 0.5f;

	float shadowBias = 0.3f;
	float maximumLightDistance = 20;

	float timeOffset = 1;
	float lightFlickerIntensity = 1;
	float lightMovementSpeed = 1;

	float lightTemperature = 0;
	float intensityScale = 0;

	float lightType = 0;

	float castsShadows = 0;
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
	//void SetQuadraticAttenuation(float intensity) { lightData.quadratic = intensity; };

	LightData GetLightData() { return lightData; };

	void UpdateLight() { lightData.lightPos = transform[3]; };

private:
	LightData lightData;
};