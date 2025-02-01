#include <GL/glew.h>
#include <iostream>
#include <GLFW/glfw3.h>
#include "Shader.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Camera.h"
#include <sstream>
#include <string>
#include "Application.h"
#include "FrameBuffer.h"
#include "RenderBuffer.h"
#include "TextureBuffer.h"
#include "VertexArray.h"
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

int main(void)
{
	float vertices[] = {
		// Positions          // Colors
		// Front face
		-0.5f, -0.5f,  0.5f,     // Bottom-left
		 0.5f, -0.5f,  0.5f,     // Bottom-right
		 0.5f,  0.5f,  0.5f,     // Top-right
		-0.5f,  0.5f,  0.5f,     // Top-left

		// Back face
		/*-0.5f, -0.5f, -0.5f,     // Bottom-left
		 0.5f, -0.5f, -0.5f,     // Bottom-right
		 0.5f,  0.5f, -0.5f,     // Top-right
		-0.5f,  0.5f, -0.5f */    // Top-left
	};
	float colors[] = {
		1.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 1.0f,
		1.0f, 1.0f, 0.0f,

		/*1.0f, 0.0f, 1.0f,
		0.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		0.5f, 0.5f, 0.5f*/
	};
	GLuint indices[] = {
		// Front face
		0, 1, 2,   2, 3, 0,

		// Back face
	   /* 4, 5, 6,   6, 7, 4,

		// Left face
		4, 0, 3,   3, 7, 4,

		// Right face
		1, 5, 6,   6, 2, 1,

		// Top face
		3, 2, 6,   6, 7, 3,

		// Bottom face
		4, 5, 1,   1, 0, 4*/
	};
	GLFWwindow* window;

	bool old = false;


	int size = sizeof(vertices);
	for (int i = 0; i < size; i++) {
		Vertex vertex;

		vertex.postion = fvec3(
			vertices[i],
			vertices[i + 1],
			vertices[i + 2]);
		//std::cout << vertex.postion.x << vertex.postion.y << vertex.postion.z << std::endl;

		//cube.AddVertex(vertex);
	}



	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
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
	Mesh objCube = fReader.Read((ASSETSPATH + OBJPATH), false);
	// ----------------------------------------------------------------------------- //

	VertexArray sva;
	VertexBuffer* svb = new VertexBuffer(sizeof(vertices) * 3, &vertices[0]);
	VertexBufferLayout slayout;
	slayout.Push<float>(3);
	slayout.Push<float>(2);
	sva.AddBuffer(*svb, slayout);

	IndexBuffer sib(&indices[0], sizeof(indices));

	// ----------------------------------------------------------------------------- //

	FrameBuffer fb(GL_FRAMEBUFFER);

	// generate texture
	TextureBuffer tb(GL_TEXTURE_2D, RESOLUTION.x, RESOLUTION.y);
	tb.Unbind();
	// attach it to currently bound framebuffer object
	tb.AttachToFrameBuffer(GL_FRAMEBUFFER);

	RenderBuffer rb(RESOLUTION.x, RESOLUTION.y);
	rb.Unbind();
	rb.AttachToFrameBuffer(GL_FRAMEBUFFER);

	fb.CheckStatus();

	fb.Unbind();
	// ----------------------------------------------------------------------------- //

	Shader shaderProgram = Shader(SHADERPATH + VERTEXPATH, SHADERPATH + FRAGMENTPATH);

	Shader screenShader = Shader(SHADERPATH + "ScreenShader.vert", SHADERPATH + "ScreenShader.frag");

	// ----------------------------------------------------------------------------- //
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glm::mat4 view;
	Camera camera(vec3(0.0f, 0.0f, -10.0f), glm::vec3(0, 1, 0));
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	Renderer renderer;
	glm::mat4 model = glm::mat4(1.0f);

	//model = translate(model, vec3(-4, 0, 0));
	//model = glm::scale(model, vec3(1,1,1));

/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		renderer.Clear();
		shaderProgram.Use();
		//glEnable(GL_DEPTH_TEST);
		float currentTime = glfwGetTime();

		shaderProgram.SetFloat("time", currentTime);

		// All transformations are to be applied to the model matrix
		//model = glm::rotate(model, glm::radians(1.0f), glm::vec3(0.0f, 0.01f, 0.0f));
		shaderProgram.SetMatrix4("model", model);

		// Camera transform
		glm::mat4 view = glm::mat4(1.0f);
		//glm::vec3 viewPos = glm::vec3(0.0f, 0.0f, -60.0f);
		//view = glm::translate(view, viewPos);

		camera.Update(window);
		view = camera.GetViewMatrix();
		//PrintMatrix(view);
		shaderProgram.SetMatrix4("view", view);
		shaderProgram.SetVector3("viewPos", view[3]);
		// projection
		glm::mat4 projection;
		projection = glm::perspective(glm::radians(45.0f), (float)RESOLUTION.x / RESOLUTION.y, 0.1f, 100.0f);
		//projection = glm::ortho(0.0f, (float)RESOLUTION.x, 0.0f, (float)RESOLUTION.y, 0.1f, 100.0f);

		shaderProgram.SetMatrix4("projection", projection);

		/* Render here */
		//fb.Bind();
		//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // we're not using the stencil buffer now
		//glEnable(GL_DEPTH_TEST);
		renderer.Draw(objCube, shaderProgram);


		//model = translate(model, vec3(4,0,0));
		//shaderProgram.SetMatrix4("model", model);

		//renderer.Draw(va, ib, shaderProgram);

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}