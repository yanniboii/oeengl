#include "Camera.h"

#include <iostream>

Camera::Camera(vec3 position, fvec3 worldUp)
	: m_Position(position), worldUp(worldUp), yaw(90.0f), pitch(0.0f)
{
	cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	UpdateCameraVectors();
}

Camera::~Camera()
{
}

void Camera::Move(GLFWwindow* window)
{
	const float speed = 0.003f;
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		m_Position += speed * cameraFront;
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		m_Position -= speed * cameraFront;
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		m_Position += speed * cameraRight;
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		m_Position -= speed * cameraRight;
	}
}


void Camera::Rotate(GLFWwindow* window)
{
	float speed = 0.4;
	double xPos = oldX, yPos = oldY;
	//glfwGetCursorPos(window, &xPos, &yPos);
	if (glfwGetKey(window, GLFW_KEY_UP))
		yPos += -speed;
	if (glfwGetKey(window, GLFW_KEY_DOWN))
		yPos += speed;
	if (glfwGetKey(window, GLFW_KEY_RIGHT))
		xPos += speed;
	if (glfwGetKey(window, GLFW_KEY_LEFT))
		xPos += -speed;
	// Calculate mouse movement deltas
	double xOffset = xPos - oldX;
	double yOffset = oldY - yPos;
	oldX = xPos;
	oldY = yPos;

	const float sensitivity = 0.1f;
	xOffset *= sensitivity;
	yOffset *= sensitivity;

	yaw += xOffset;
	pitch += yOffset;

	// Constrain pitch to avoid gimbal lock
	if (pitch > 89.0f) pitch = 89.0f;
	if (pitch < -89.0f) pitch = -89.0f;

	UpdateCameraVectors();
}

void Camera::ProcessInput(GLFWwindow* window)
{
	Move(window);
	Rotate(window);
}

void Camera::Update(GLFWwindow* window)
{
	ProcessInput(window);
	m_ViewMatrix[3][0] = m_Position.x;
	m_ViewMatrix[3][1] = m_Position.y;
	m_ViewMatrix[3][2] = m_Position.z;
}

glm::mat4 Camera::GetViewMatrix()
{
	// Create the view matrix using LookAt
	return glm::lookAt(m_Position, m_Position + cameraFront, cameraUp);
}

void Camera::UpdateCameraVectors()
{
	glm::vec3 front;
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	cameraFront = glm::normalize(front);

	cameraRight = glm::normalize(glm::cross(cameraFront, worldUp));
	cameraUp = glm::normalize(glm::cross(cameraRight, cameraFront));
}
