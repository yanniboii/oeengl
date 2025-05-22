#include <GL/glew.h>
#include <iostream>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <sstream>
#include <string>
#include "Application.h"
#include "Abstraction/HighAbstraction/Renderer.h"
#include <algorithm>
#include "ModelLoading/ObjFileReader.h"

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

float GetFPS()
{
	static double lastTime = glfwGetTime();

	static int frameCount = 0;

	double currentTime = glfwGetTime();
	frameCount++;

	static float fps = 0;
	if (currentTime - lastTime >= 1) {
		fps = frameCount / (currentTime - lastTime);
		frameCount = 0;
		lastTime = currentTime;
	}

	return fps;
}

void UpdateWindowTitle(GLFWwindow* window, int fps) {
	static int lastFPS = 0;
	if (fps != lastFPS) {
		std::string title = "OpenGL Program - FPS: " + std::to_string(fps);
		glfwSetWindowTitle(window, title.c_str());
	}
	lastFPS = fps;
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
	glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
	glEnable(GL_DEBUG_OUTPUT);
	glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
	glDebugMessageCallback(messageCallback, 0);
	glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_NOTIFICATION, 0, NULL, GL_FALSE);

	// ----------------------------------------------------------------------------- //

	ObjFileReader fReader;
	Mesh* objCube = fReader.Read((ASSETSPATH + OBJPATH), false);

	// ----------------------------------------------------------------------------- //

	Shader* shaderProgram = new Shader(SHADERPATH + VERTEXPATH, SHADERPATH + FRAGMENTPATH);

	// ----------------------------------------------------------------------------- //

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
	//light2->SetDiffuseIntensity(20);
	//light2->SetSpecularIntensity(20);
	light2->UpdateLight();

	light3->SetPosition(glm::vec3(1000, 1, 1));
	light3->SetLightType(1);
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
	//scene->AddLight(light3);

	renderer.InitializePostProcessing();

	glEnable(GL_DEPTH_TEST);
	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		renderer.Clear();
		float val = (glm::cos(glm::radians(glfwGetTime()) * 70) + 1) / 2.0f;
		light->SetQuadraticAttenuation(val);
		light->SetLinearAttenuation(val / 3);

		camera->Update(window);

		renderer.Draw(scene);

		UpdateWindowTitle(window, GetFPS());

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}