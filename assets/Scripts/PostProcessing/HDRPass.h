#pragma once
#include "../Abstraction/HighAbstraction/PostProcessing.h"

class HDRPass : public PostProcessing {
public:
	HDRPass(Shader* shader);

	HDRPass();

	void BeforeRender(const PostProcessingParams params) override;

	void AfterRender(const PostProcessingParams params) override;

private:

};
