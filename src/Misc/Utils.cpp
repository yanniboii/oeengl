#include <GLFW/glfw3.h>

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
