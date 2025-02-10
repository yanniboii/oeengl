#include "Material.h"
#include "Scene.h"

Material::Material(Shader* shader) : shader(shader), color(glm::vec3(1, 1, 1))
{

}

Material::Material(Shader* shader, glm::vec3 color) : shader(shader), color(color)
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

	shader->SetFloat("time", currentTime);
	shader->SetVector3("m_Ambient", color);
	shader->SetVector3("m_Diffuse", light.GetLightColor());
	shader->SetVector3("m_LightPos", light.GetPosition());

	shader->SetVector3("viewPos", view[3]);

	shader->SetMatrix4("model", model);
	shader->SetMatrix4("view", view);
	shader->SetMatrix4("projection", projection);

}

glm::vec3 Material::GetColor()
{
	return color;
}

void Material::SetColor(glm::vec3 color)
{
	this->color = color;
}
