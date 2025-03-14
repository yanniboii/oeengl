#include <GL/glew.h>
#include <iostream>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <sstream>
#include <string>
#include "Application.h"
#include "Abstraction/LowAbstraction/FrameBuffer.h"
#include "Abstraction/LowAbstraction/RenderBuffer.h"
#include "Abstraction/LowAbstraction/TextureBuffer.h"
#include "Abstraction/HighAbstraction/Renderer.h"
#include <algorithm>
#include "ModelLoading/ObjFileReader.h"

const std::string ASSETSPATH = "C:/Dev/oeengl/assets/";
const std::string SHADERPATH = "C:/Dev/oeengl/assets/Shaders/";
const std::string VERTEXPATH = "VertexShader.vert";
const std::string FRAGMENTPATH = "FragmentShader.frag";
const std::string OBJPATH = "Models/teapot.obj";
// C: / Dev / oeengl / assets / Shaders / VertexShader.vert

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

	const char* version = (const char*)glGetString(GL_VERSION);
	std::cout << "OpenGL Version: " << version << std::endl;

	// Set a clear color
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glEnable(GL_DEBUG_OUTPUT);
	glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
	glDebugMessageCallback(messageCallback, 0);
	glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_NOTIFICATION, 0, NULL, GL_FALSE);

	// ----------------------------------------------------------------------------- //

	ObjFileReader fReader;
	Mesh* objCube = fReader.Read((ASSETSPATH + OBJPATH), false);


	float vertices[] = {
		// Positions
		-0.5f, -0.5f, 0.0f, 0.0f, // Bottom-left
		 0.5f, -0.5f, 1.0f, 0.0f, // Bottom-right
		 0.5f,  0.5f, 1.0f, 1.0f, // Top-right
		-0.5f,  0.5f, 0.0f, 1.0f  // Top-left
	};
	GLuint indices[] = {
		0, 1, 2,
		2, 3, 0
	};

	int size = sizeof(vertices);
	std::vector<Vertex> verts;
	for (int i = 0; i < size; i++) {
		Vertex vertex;
		vertex.postion = fvec3(
			vertices[i],
			vertices[i + 1],
			vertices[i + 2]);
		//std::cout << vertex.postion.x << vertex.postion.y << vertex.postion.z << std::endl;
		verts.push_back(vertex);
	}

	VertexBuffer* vb = new VertexBuffer(sizeof(vertices) * 4, &vertices[0]);

	VertexBufferLayout layout;
	layout.Push<float>(2);
	layout.Push<float>(2);
	VertexArray* va = new VertexArray;
	va->AddBuffer(*vb, layout);
	IndexBuffer* ib = new IndexBuffer;
	ib = new IndexBuffer(&indices[0], sizeof(indices));


	Mesh* cube = new Mesh(va, ib);

	FrameBuffer fb(GL_FRAMEBUFFER);

	TextureBuffer tb(GL_TEXTURE_2D, RESOLUTION.x, RESOLUTION.y);
	tb.Unbind();
	tb.AttachToFrameBuffer(GL_FRAMEBUFFER);

	RenderBuffer rb(RESOLUTION.x, RESOLUTION.y);
	rb.Unbind();
	rb.AttachToFrameBuffer(GL_FRAMEBUFFER);
	// attach it to currently bound framebuffer object
	fb.CheckStatus();
	// ----------------------------------------------------------------------------- //

	Shader* shaderProgram = new Shader(SHADERPATH + VERTEXPATH, SHADERPATH + FRAGMENTPATH);

	Shader screenShader = Shader(SHADERPATH + "ScreenShader.vert", SHADERPATH + "ScreenShader.frag");
	// ----------------------------------------------------------------------------- //

	glm::mat4 view;
	Camera* camera = new Camera(vec3(0.0f, 0.0f, -10.0f), glm::vec3(0, 1, 0));

	Renderer renderer;
	renderer.SetActiveCamera(camera);

	Material* mat = new Material(shaderProgram, glm::vec4(0.0f, 0.0f, 1.0f, 1.0f));
	RenderObject* ro = new RenderObject(objCube, mat);

	Scene* scene = new Scene();

	GameObject* go = new GameObject();
	GameObject* go2 = new GameObject();
	GameObject* go3 = new GameObject();
	Light* light = new Light();
	Light* light2 = new Light();
	Light* light3 = new Light();

	light->SetPosition(glm::vec3(15, 9, 2));
	light->SetLightType(0);
	light->UpdateLight();

	light2->SetPosition(glm::vec3(1, 10, 2));
	light2->UpdateLight();

	light3->SetPosition(glm::vec3(0, 0, 10));
	light3->UpdateLight();

	go2->SetPosition(glm::vec3(2, 2, 2));
	go3->SetPosition(glm::vec3(15, 2, 2));

	go->AddRenderObject(ro);
	go2->AddRenderObject(ro);
	go3->AddRenderObject(ro);

	scene->AddChild(go);
	go->AddChild(go2);
	go2->AddChild(go3);
	scene->AddLight(light);
	scene->AddLight(light2);
	scene->AddLight(light3);

	glEnable(GL_DEPTH_TEST);
	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		renderer.Clear();
		float val = (glm::cos(glm::radians(glfwGetTime()) * 70) + 1) / 2.0f;
		light->SetQuadraticAttenuation(val);
		light->SetLinearAttenuation(val / 3);


		camera->Update(window);

		rb.Bind();
		fb.Bind();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // we're not using the stencil buffer now
		glEnable(GL_DEPTH_TEST);

		renderer.Draw(scene);

		fb.Unbind();
		rb.Unbind();
		glDisable(GL_DEPTH_TEST);

		//glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
		//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // we're not using the stencil buffer now
		tb.Bind();

		//screenShader.Use();
		renderer.Draw(*va, *ib, screenShader);
		tb.Unbind();


		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}