#pragma once
#include "../Abstraction/HighAbstraction/PostProcessing.h"

class GaussianBlurPass : public PostProcessing {
public:
	GaussianBlurPass(Shader* shader, std::vector<float> kernel, std::vector<glm::vec2> kernelOffsets);

	GaussianBlurPass();

	void BeforeRender(const PostProcessingParams params) override;

	void AfterRender(const PostProcessingParams params) override;

private:

};