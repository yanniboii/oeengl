#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <iostream>

class Shader {
public:
	GLuint ID;

	Shader(const std::string vertexPath, const std::string fragmentPath);

	Shader(const char* shaderPath);

	~Shader();

	void Use() const;

	void SetBool(const GLchar* valueName, bool value);
	void SetInt(const GLchar* valueName, int value);
	void SetFloat(const GLchar* valueName, float value);

	void SetVector2(const GLchar* valueName, glm::vec2 value);
	void SetVector3(const GLchar* valueName, glm::vec3 value);
	void SetVector4(const GLchar* valueName, glm::vec4 value);

	void SetMatrix2(const GLchar* valueName, glm::mat2 value);
	void SetMatrix2x3(const GLchar* valueName, glm::mat2x3 value);
	void SetMatrix2x4(const GLchar* valueName, glm::mat2x4 value);

	void SetMatrix3(const GLchar* valueName, glm::mat3 value);
	void SetMatrix3x2(const GLchar* valueName, glm::mat3x2 value);
	void SetMatrix3x4(const GLchar* valueName, glm::mat3x4 value);

	void SetMatrix4(const GLchar* valueName, glm::mat4 value);
	void SetMatrix4x2(const GLchar* valueName, glm::mat4x2 value);
	void SetMatrix4x3(const GLchar* valueName, glm::mat4x3 value);
private:

};