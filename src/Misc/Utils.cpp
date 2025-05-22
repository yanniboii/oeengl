#include <GLFW/glfw3.h>
#include "Utils.h"

float GetDeltaTime()
{
	static float lastTime = glfwGetTime();

	float currentTime = glfwGetTime();

	float deltaTime = 0;

	if (lastTime != currentTime)
	{
		deltaTime = currentTime - lastTime;
		lastTime = currentTime;
	}

	return deltaTime;
}

void CheckOutOfRangeVector(size_t vectorSize, unsigned int index)
{
	if (index > static_cast<int>(vectorSize)) {
		throw std::out_of_range("Invalid position");
	}
}
