#include "PostProcessingDefaults.h"

namespace PostProcessingDefaults {
	Shader* GetDefaultShader() {
		Shader* shader = new Shader(SHADERPATH + "HorizontalSS.vert", SHADERPATH + "HorizontalSS.frag");
		return shader;
	}

	std::vector<float> kernel = { 2.0f, 4.0f, 2.0f };

	std::vector<glm::vec2> kernelOffsets = {
		glm::vec2((1.0f / RESOLUTION.x), 0.0f),
		glm::vec2(0.0f,  0.0f),
		glm::vec2(-(1.0f / RESOLUTION.x), 0.0f)
	};
}