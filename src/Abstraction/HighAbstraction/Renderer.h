#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Scene.h"
#include "Camera.h"
#include "../LowAbstraction/FrameBuffer.h"
#include "../LowAbstraction/RenderBuffer.h"
#include "../LowAbstraction/TextureBuffer.h"

enum PostProcessing {
	None = 0,
	Normal = 1,
	PingPong = 2
};

class Renderer {
public:
	void Draw(const VertexArray& va, const IndexBuffer& ib, const  Shader& shader) const;
	void Draw(Scene* scene) const;
	void Draw(Scene* scene, GameObject* go, bool recursive = false) const;
	void Draw(Scene* scene, RenderObject& ro, glm::mat4 model, glm::mat4 view, glm::mat4 projection) const;
	void Draw(Mesh& mesh, const Shader& shader) const;

	void InitializePostProcessing(const PostProcessing postProcessing = None);

	void Clear();

	void SetActiveCamera(Camera* camera);

	int pingPongAmount = 0;
private:
	Camera* camera;

	VertexArray* postProcessingVA;
	IndexBuffer* postProcessingIB;

	RenderBuffer* renderBuffer;

	FrameBuffer* frameBuffer_A;
	TextureBuffer* textureBuffer_A;

	FrameBuffer* frameBuffer_B;
	TextureBuffer* textureBuffer_B;

	Shader* screenShader;
	Shader* screenShaderHor;
	Shader* screenShaderVert;

	PostProcessing postProcessing = None;
};