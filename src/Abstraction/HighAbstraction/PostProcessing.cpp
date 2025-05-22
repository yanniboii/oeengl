#include "PostProcessing.h"


PostProcessing::PostProcessing(
	Shader* shader,
	std::vector<float> kernel,
	std::vector<glm::vec2> kernelOffsets) :
	shader(shader),
	kernel(kernel),
	kernelOffsets(kernelOffsets)
{

}

PostProcessing::PostProcessing(Shader* shader) : shader(shader)
{
}

PostProcessing::PostProcessing() :
	kernel(PostProcessingDefaults::kernel),
	kernelOffsets(PostProcessingDefaults::kernelOffsets)
{

}

void PostProcessing::BeforeRender(const PostProcessingParams params)
{
}

void PostProcessing::AfterRender(const PostProcessingParams params)
{
}

void PostProcessing::UpdateShader(Shader* shader)
{
	this->shader = shader;
}

void PostProcessing::UpdateKernel(std::vector<float> kernel)
{
	this->kernel = kernel;
}

void PostProcessing::UpdateKernelOffsets(std::vector<glm::vec2> kernelOffsets)
{
	this->kernelOffsets = kernelOffsets;
}

Shader* PostProcessing::GetShader()
{
	return shader;
}
