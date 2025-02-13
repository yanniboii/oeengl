#include "Material.h"
#include "Scene.h"

Material::Material(Shader* shader) :
	shader(shader),
	ambientColor(glm::vec4(1, 1, 1, 1)),
	diffuseColor(glm::vec4(1, 0.9f, 0.6f, 1)),
	specularColor(glm::vec4(0.1f, 1, 0.1f, 1)),
	ambientCoefficient(0.4f),
	diffuseCoefficient(0.7f),
	specularShininess(256),
	specularCoefficient(0.8f)
{

}

Material::Material(Shader* shader, glm::vec4 color) :
	shader(shader),
	ambientColor(color),
	diffuseColor(glm::vec4(1, 0.9f, 0.6f, 1)),
	specularColor(glm::vec4(0.1f, 1, 0.1f, 1)),
	ambientCoefficient(0.4f),
	diffuseCoefficient(0.7f),
	specularCoefficient(256),
	specularShininess(0.8f)
{

}

Material::~Material()
{
}

void Material::Render(glm::mat4 model, glm::mat4 view, glm::mat4 projection, Scene* scene)
{
	shader->Use();

	float currentTime = glfwGetTime();

	Light light = *scene->GetLights()[0];
	LightData lightData = light.GetLightData();

	shader->SetFloat("time", currentTime);

	// ----------------------------------------------------------------------------- //

	shader->SetVector4("material.ambientColor", ambientColor);
	shader->SetVector4("material.diffuseColor", diffuseColor);
	shader->SetVector4("material.specularColor", specularColor);

	shader->SetFloat("material.ambientCoefficient", ambientCoefficient);
	shader->SetFloat("material.diffuseCoefficient", diffuseCoefficient);
	shader->SetFloat("material.specularCoefficient", specularCoefficient);

	shader->SetFloat("material.specularShininess", specularShininess);

	// ----------------------------------------------------------------------------- //

	shader->SetVector4("light.ambientColor", lightData.ambientColor);
	shader->SetVector4("light.diffuseColor", lightData.diffuseColor);
	shader->SetVector4("light.specularColor", lightData.specularColor);

	shader->SetFloat("light.ambientIntensity", lightData.ambientIntensity);
	shader->SetFloat("light.diffuseIntensity", lightData.diffuseIntensity);
	shader->SetFloat("light.specularIntensity", lightData.specularIntensity);

	shader->SetFloat("light.constant", lightData.constant);
	shader->SetFloat("light.linear", lightData.linear);
	shader->SetFloat("light.quadratic", lightData.quadratic);

	// ----------------------------------------------------------------------------- //

	shader->SetVector3("m_LightPos", light.GetPosition());

	shader->SetVector3("viewPos", view[3]);

	shader->SetMatrix4("model", model);
	shader->SetMatrix4("view", view);
	shader->SetMatrix4("projection", projection);

}

glm::vec4 Material::GetColor()
{
	return ambientColor;
}

void Material::SetColor(glm::vec4 color)
{
	this->ambientColor = color;
}
