#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Scene.h"
#include "Camera.h"
#include "../LowAbstraction/FrameBuffer.h"
#include "../LowAbstraction/RenderBuffer.h"
#include "../LowAbstraction/TextureBuffer.h"
#include "../HighAbstraction/PostProcessingFactory.h"
#include "../Application.h"

class Renderer {
public:
	void PingPongPass() const;

	void Draw(const VertexArray& va, const IndexBuffer& ib, const  Shader& shader) const;
	void Draw(Scene* scene) const;
	void Draw(Scene* scene, GameObject* go, bool recursive = false) const;
	void Draw(Scene* scene, RenderObject& ro, glm::mat4 model, glm::mat4 view, glm::mat4 projection) const;
	void Draw(Mesh& mesh, const Shader& shader) const;

	void PrintData(PostProcessingParams params, FrameBuffer* framebuffer) const;

	void InitializePostProcessing();

	void Clear();

	void SetActiveCamera(Camera* camera);

	void SetPrintData(bool print);

private:
	Camera* camera;
	glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)RESOLUTION.x / RESOLUTION.y, 0.1f, 100.0f);

	VertexArray* postProcessingVA;
	IndexBuffer* postProcessingIB;

	RenderBuffer* renderBuffer;

	FrameBuffer* frameBuffer_A;
	TextureBuffer* textureBuffer_A;

	FrameBuffer* frameBuffer_B;
	TextureBuffer* textureBuffer_B;

	FrameBuffer* baseFBO;
	TextureBuffer* baseTexture;

	TextureBuffer* attachment1;
	TextureBuffer* attachment2;
	TextureBuffer* depthTexture;

	Shader* screenShader;
	Shader* screenShaderHor;
	Shader* screenShaderVert;
	Shader* combineShader;

	std::vector<PostProcessing*> postProccessing;

	bool printNextframeData = false;
};