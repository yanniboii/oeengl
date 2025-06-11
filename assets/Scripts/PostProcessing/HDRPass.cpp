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

	GLenum drawBuffers[2] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1 };
	glDrawBuffers(2, drawBuffers);

	shader->Use();

	shader->SetFloat("exposure", 0.6f);


	if (params.firstPass) {
		params.baseTexture->Bind(GL_TEXTURE0);
		shader->SetInt("baseTexture", 0);
	}
	else {
		params.previousTexture_0->Bind(GL_TEXTURE0);
		shader->SetInt("baseTexture", 0);
	}

	params.depthTexture->Bind(GL_TEXTURE1);
	shader->SetInt("depthTexture", 1);
}

void HDRPass::AfterRender(const PostProcessingParams params)
{

}
