#include "CombinePass.h"
#include "../Abstraction/HighAbstraction/PostProcessingFactory.h"

REGISTER_POSTPROCESSING_EFFECT(CombinePass, CombinePass)

CombinePass::CombinePass(Shader* shader) : PostProcessing(shader)
{
}

CombinePass::CombinePass()
{
}

void CombinePass::BeforeRender(const PostProcessingParams params)
{
	if (params.lastPass)
		params.nextFrameBuffer->Unbind();
	else
		params.nextFrameBuffer->Bind();

	shader->Use();

	params.previousTexture_0->Bind(GL_TEXTURE0);
	shader->SetInt("texture1", 0);

	params.previousTexture_1->Bind(GL_TEXTURE1);
	shader->SetInt("texture2", 1);
}

void CombinePass::AfterRender(const PostProcessingParams params)
{
	params.previousTexture_0->Unbind();
}
