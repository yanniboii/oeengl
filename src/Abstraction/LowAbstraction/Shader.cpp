#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"

Shader::Shader(const std::string vertexPath, const std::string fragmentPath)
{
	std::string vertexCode, fragmentCode;
	std::ifstream vertexFile, fragmentFile;

	//vertexFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	//fragmentFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try {
		vertexFile.open(vertexPath.c_str());
		if (!vertexFile) {
			std::cerr << "ERROR::SHADER::VERTEX_FILE_NOT_OPENED: " << vertexPath << std::endl;
			return;
		}
		fragmentFile.open(fragmentPath.c_str());
		if (!fragmentFile) {
			std::cerr << "ERROR::SHADER::FRAGMENT_FILE_NOT_OPENED: " << fragmentPath << std::endl;
			return;
		}

		std::stringstream vertexStream, fragmentStream;

		vertexStream << vertexFile.rdbuf();
		fragmentStream << fragmentFile.rdbuf();

		vertexFile.close();
		fragmentFile.close();

		vertexCode = vertexStream.str();
		fragmentCode = fragmentStream.str();
	}
	catch (std::ifstream::failure exc) {
		std::cout << "STREAM ERROR " << std::endl;
	}
	const char* vertexShaderCode = vertexCode.c_str();
	const char* fragmentShaderCode = fragmentCode.c_str();

	GLuint vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShaderID, 1, &vertexShaderCode, NULL);
	glCompileShader(vertexShaderID);

	int vSucces;
	char vInfo[512];
	glGetShaderiv(vertexShaderID, GL_COMPILE_STATUS, &vSucces);
	if (!vSucces) {
		glGetShaderInfoLog(vertexShaderID, 512, NULL, vInfo);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << vInfo << std::endl;
	}

	GLuint fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShaderID, 1, &fragmentShaderCode, NULL);
	glCompileShader(fragmentShaderID);

	int fSucces;
	char fInfo[512];
	glGetShaderiv(fragmentShaderID, GL_COMPILE_STATUS, &fSucces);
	if (!fSucces) {
		glGetShaderInfoLog(fragmentShaderID, 512, NULL, fInfo);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << fInfo << std::endl;
	}

	ID = glCreateProgram();
	glAttachShader(ID, vertexShaderID);
	glAttachShader(ID, fragmentShaderID);
	glLinkProgram(ID);

	int sSucces;
	char sInfo[512];
	glGetProgramiv(ID, GL_LINK_STATUS, &sSucces);
	if (!sSucces) {
		glGetProgramInfoLog(ID, 512, NULL, sInfo);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << sInfo << std::endl;
	}

	glDeleteShader(vertexShaderID);
	glDeleteShader(fragmentShaderID);

}

Shader::Shader(const char* shaderPath)
{
	ID = glCreateProgram();
}

Shader::~Shader()
{
	glDeleteProgram(ID);
}

void Shader::Use() const
{
	glUseProgram(ID);
}

void Shader::SetBool(const GLchar* valueName, bool value)
{
	int valueLoc = glGetUniformLocation(ID, valueName);
	glUniform1i(valueLoc, value);
}

void Shader::SetInt(const GLchar* valueName, int value)
{
	int valueLoc = glGetUniformLocation(ID, valueName);
	glUniform1i(valueLoc, value);
}

void Shader::SetFloat(const GLchar* valueName, float value) {
	int valueLoc = glGetUniformLocation(ID, valueName);
	glUniform1f(valueLoc, value);
}

void Shader::SetVector2(const GLchar* valueName, glm::vec2 value)
{
	int valueLoc = glGetUniformLocation(ID, valueName);
	glUniform2fv(valueLoc, 1, glm::value_ptr(value));
}

void Shader::SetVector3(const GLchar* valueName, glm::vec3 value)
{
	int valueLoc = glGetUniformLocation(ID, valueName);
	glUniform3fv(valueLoc, 1, glm::value_ptr(value));
}

void Shader::SetVector4(const GLchar* valueName, glm::vec4 value)
{
	int valueLoc = glGetUniformLocation(ID, valueName);
	glUniform4fv(valueLoc, 1, glm::value_ptr(value));
}

void Shader::SetFloatArray(const GLchar* valueName, std::vector<float> value)
{
	int valueLoc = glGetUniformLocation(ID, valueName);
	glUniform1fv(valueLoc, value.size(), value.data());
}

void Shader::SetVector2Array(const GLchar* valueName, std::vector<glm::vec2> value)
{
	int valueLoc = glGetUniformLocation(ID, valueName);
	glUniform2fv(valueLoc, value.size(), glm::value_ptr(value[0]));
}

void Shader::SetMatrix4(const GLchar* valueName, glm::mat4 value)
{
	int valueLoc = glGetUniformLocation(ID, valueName);
	glUniformMatrix4fv(valueLoc, 1, GL_FALSE, glm::value_ptr(value));
}
