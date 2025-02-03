#include <GL/glew.h>
#include <iostream>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Camera.h"
#include <sstream>
#include <string>
#include "Application.h"
#include "FrameBuffer.h"
#include "RenderBuffer.h"
#include "TextureBuffer.h"
#include "Renderer.h"
#include <algorithm>
#include "ModelLoading/ObjFileReader.h"

const std::string ASSETSPATH = "C:/Dev/oeengl/assets/";
const std::string SHADERPATH = "C:/Dev/oeengl/assets/Shaders/";
const std::string VERTEXPATH = "VertexShader.vert";
const std::string FRAGMENTPATH = "FragmentShader.frag";
const std::string OBJPATH = "Models/teapot.obj";
// C: / Dev / oeengl / assets / Shaders / VertexShader.vert
const glm::ivec2 RESOLUTION = glm::ivec2(1920 / 2, 1080 / 2);

void PrintMatrix(glm::mat4& view)
{
	std::ostringstream oss;
	oss << "Matrix:\n";
	for (int i = 0; i < 4; ++i) {
		oss << "[" << view[i][0] << ", " << view[i][1] << ", "
			<< view[i][2] << ", " << view[i][3] << "]\n";
	}
	std::cout << oss.str() << std::endl;
}

void PrintMesh(std::vector<Vertex>& verts, std::vector<glm::fvec3>& vertPos, std::vector<glm::fvec3>& vertNorm, std::vector<glm::fvec3>& vertCol, std::vector<glm::fvec2>& vertUv)
{
	for (int i = 0; i < verts.size(); i++) {
		std::cout << vertPos[i].r << vertPos[i].g << vertPos[i].b << std::endl;
		std::cout << vertNorm[i].r << vertNorm[i].g << vertNorm[i].b << std::endl;
		std::cout << vertCol[i].r << vertCol[i].g << vertCol[i].b << std::endl;
		std::cout << vertUv[i].x << vertUv[i].y << std::endl << std::endl;
	}
}

void GLAPIENTRY messageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam) {
	std::cout << message << std::endl;

}

int main(void)
{

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	GLFWwindow* window;
	window = glfwCreateWindow(RESOLUTION.x, RESOLUTION.y, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	glfwSetWindowPos(window, 500, 400);

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	if (glewInit() != GLEW_OK) {
		std::cout << "Failed to initialize GLEW" << std::endl;
		return -1;
	}

	// Set a clear color
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

	// ----------------------------------------------------------------------------- //

	ObjFileReader fReader;
	Mesh* objCube = fReader.Read((ASSETSPATH + OBJPATH), false);

	// ----------------------------------------------------------------------------- //

	Shader* shaderProgram = new Shader(SHADERPATH + VERTEXPATH, SHADERPATH + FRAGMENTPATH);

	// ----------------------------------------------------------------------------- //
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glm::mat4 view;
	Camera camera(vec3(0.0f, 0.0f, -10.0f), glm::vec3(0, 1, 0));

	Renderer renderer;
	glm::mat4 model = glm::mat4(1.0f);

	Material* mat = new Material(shaderProgram);
	RenderObject ro = RenderObject(objCube, mat);

	glEnable(GL_DEBUG_OUTPUT);
	glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
	glDebugMessageCallback(messageCallback, 0);
	glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_NOTIFICATION, 0, NULL, GL_FALSE);
	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		renderer.Clear();

		// Camera transform
		glm::mat4 view = glm::mat4(1.0f);

		camera.Update(window);
		view = camera.GetViewMatrix();

		// projection
		glm::mat4 projection;
		projection = glm::perspective(glm::radians(45.0f), (float)RESOLUTION.x / RESOLUTION.y, 0.1f, 100.0f);
		//projection = glm::ortho(0.0f, (float)RESOLUTION.x, 0.0f, (float)RESOLUTION.y, 0.1f, 100.0f);

		mat->Render(model, view, projection);
		renderer.Draw(*objCube, *shaderProgram);

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}