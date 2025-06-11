#include "GausianBlurPass.h"
#include "../Abstraction/HighAbstraction/PostProcessingFactory.h"

REGISTER_POSTPROCESSING_EFFECT(GaussianBlurPass, GaussianBlurPass)
REGISTER_POSTPROCESSING_EFFECT(GaussianBlurPass, GaussianBlurPassHorizontal)
REGISTER_POSTPROCESSING_EFFECT(GaussianBlurPass, GaussianBlurPassVertical)

GaussianBlurPass::GaussianBlurPass(Shader* shader,
	std::vector<float> kernel,
	std::vector<glm::vec2> kernelOffsets) :
	PostProcessing(shader, kernel, kernelOffsets)
{

}

GaussianBlurPass::GaussianBlurPass()
{
}

void GaussianBlurPass::BeforeRender(const PostProcessingParams params)
{
	if (params.lastPass)
		params.nextFrameBuffer->Unbind();
	else
		params.nextFrameBuffer->Bind();

	shader->Use();

	shader->SetBool("firstPass", params.firstPass);

	shader->SetFloatArray("kernel", kernel);
	shader->SetVector2Array("kernelOffsets", kernelOffsets);
	shader->SetInt("kernelSize", kernel.size());

	params.baseTexture->Bind(GL_TEXTURE1);
	shader->SetInt("baseTex", 1);

	params.previousTexture_1->Bind(GL_TEXTURE0);
	shader->SetInt("colorTex", 0);
}

void GaussianBlurPass::AfterRender(const PostProcessingParams params)
{
	params.previousTexture_0->Unbind();
}
