#pragma once
#include "../Abstraction/HighAbstraction/PostProcessing.h"

class CombinePass : public PostProcessing {
public:
	CombinePass(Shader* shader);

	CombinePass();

	void BeforeRender(const PostProcessingParams params) override;

	void AfterRender(const PostProcessingParams params) override;

private:

};