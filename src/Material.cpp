#include "Material.h"

Material::Material(Shader* shader) : mShader(shader)
{

}

Material::~Material()
{
}

void Material::Render(glm::mat4 model, glm::mat4 view, glm::mat4 projection)
{
	mShader->Use();

	float currentTime = glfwGetTime();

	mShader->SetFloat("time", currentTime);

	mShader->SetVector3("viewPos", view[3]);

	mShader->SetMatrix4("model", model);
	mShader->SetMatrix4("view", view);
	mShader->SetMatrix4("projection", projection);

}

glm::vec4 Material::GetColor()
{
	return glm::vec4();
}

void Material::SetColor(glm::vec4 color)
{
	this->color = color;
}
