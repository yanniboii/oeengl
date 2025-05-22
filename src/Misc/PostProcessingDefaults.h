#pragma once
#include "../Abstraction/LowAbstraction/Shader.h"
#include "Utils.h"
#include "../Application.h"

namespace PostProcessingDefaults {
	extern Shader* shader;

	extern std::vector<float> kernel;

	extern std::vector<glm::vec2> kernelOffsets;
}