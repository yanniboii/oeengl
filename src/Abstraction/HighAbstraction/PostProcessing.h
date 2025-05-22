#pragma once
#include <vector>
#include <glm/vec2.hpp>
#include "../LowAbstraction/FrameBuffer.h"
#include "../LowAbstraction/RenderBuffer.h"
#include "../LowAbstraction/TextureBuffer.h"
#include "../LowAbstraction/Shader.h"
#include "../Misc/PostProcessingDefaults.h"

struct PostProcessingParams {
	TextureBuffer* previousTexture;
	TextureBuffer* baseTexture;
	FrameBuffer* nextFrameBuffer;

	bool firstPass;
	bool lastPass;
};

class PostProcessing {
public:
	PostProcessing(Shader* shader,
		std::vector<float> kernel,
		std::vector<glm::vec2> kernelOffsets);

	PostProcessing(Shader* shader);

	PostProcessing();

	virtual void BeforeRender(const PostProcessingParams params);

	virtual void AfterRender(const PostProcessingParams params);

	void UpdateShader(Shader* shader);

	void UpdateKernel(std::vector<float> kernel);

	void UpdateKernelOffsets(std::vector<glm::vec2> kernelOffsets);

	Shader* GetShader();

protected:
	Shader* shader = nullptr;

	std::vector<float> kernel;
	std::vector<glm::vec2> kernelOffsets;
};
