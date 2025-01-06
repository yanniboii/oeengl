#pragma once
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>

using namespace glm;

class Camera
{
public:
	Camera(vec3 position, fvec3 worldUp);
	~Camera();

	void Update(GLFWwindow *window);
	
	mat4 GetViewMatrix();
private:
	fvec3 m_Position;
	fvec3 worldUp;
	fvec3 cameraFront = vec3(0.0f,0.0f,-1.0f);
	fvec3 cameraRight = normalize(cross(cameraFront,worldUp));
	fvec3 cameraUp = normalize(cross(cameraFront,cameraRight));
	mat4 m_ViewMatrix;
	double yaw = 0;
	double pitch = 0;

	double oldX = 0;
	double oldY = 0;

	void Move(GLFWwindow* window);

	void Rotate(GLFWwindow* window);

	void ProcessInput(GLFWwindow* window);

	void UpdateCameraVectors();
};