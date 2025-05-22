#include "HDRPass.h"
#include "../Abstraction/HighAbstraction/PostProcessingFactory.h"

REGISTER_POSTPROCESSING_EFFECT(HDRPass, HDRPass)

HDRPass::HDRPass(Shader* shader) : PostProcessing(shader)
{
}

HDRPass::HDRPass()
{
}

void HDRPass::BeforeRender(const PostProcessingParams params)
{
	if (params.lastPass)
		params.nextFrameBuffer->Unbind();
	else
		params.nextFrameBuffer->Bind();

	shader->Use();

	shader->SetFloat("exposure", 1.0f);

	if (params.firstPass)
		params.baseTexture->Bind();
	else
		params.previousTexture->Bind();
}

void HDRPass::AfterRender(const PostProcessingParams params)
{

}
