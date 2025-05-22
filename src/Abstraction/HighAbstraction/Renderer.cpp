#include "Renderer.h"
#include "../../Application.h"

void Renderer::Draw(
	const VertexArray& va,
	const IndexBuffer& ib,
	const Shader& shader) const
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	shader.Use();
	va.Bind();
	ib.Bind();

	glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr);
}

void Renderer::Draw(Scene* scene) const
{
	baseFBO->Bind();
	baseTexture->Bind();
	renderBuffer->Bind();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);


	if (scene->ChildCount() <= 0)
		return;

	std::vector<GameObject*> children = scene->GetChildren();

	for (int i = 0; i < children.size(); i++)
	{
		if (children[i]->ChildCount() > 0)
			Draw(scene, children[i], true);
		else
			Draw(scene, children[i]);
	}

	screenShader->Use();


	renderBuffer->Unbind();
	baseFBO->Unbind();
	baseTexture->Unbind();

	glDisable(GL_DEPTH_TEST);

	PingPongPass();
}


void Renderer::Draw(Mesh& mesh, const Shader& shader) const
{
	Draw(mesh.GetVertexArray(), mesh.GetIndexBuffer(), shader);
}

void Renderer::PingPongPass() const
{
	PostProcessingFactory instance = PostProcessingFactory::getInstance();

	std::vector<std::shared_ptr<PostProcessing>> postProcessingQueue = instance.GetPostProcessingQueue();

	glDisable(GL_DEPTH_TEST);
	renderBuffer->Bind();
	for (int i = 0; i < postProcessingQueue.size(); i++) {

		auto currentEffect = postProcessingQueue[i];

		PostProcessingParams params;
		params.baseTexture = baseTexture;


		if (i == 0)
			params.firstPass = true;
		else
			params.firstPass = false;

		TextureBuffer* usedTexture = nullptr;
		if (i == postProcessingQueue.size() - 1)
			params.lastPass = true;
		else
			params.lastPass = false;

		if (i % 2 == 0) {
			params.previousTexture = textureBuffer_A;
			params.nextFrameBuffer = frameBuffer_B;
			usedTexture = textureBuffer_A;


			frameBuffer_A->Unbind();
		}
		else
		{
			params.previousTexture = textureBuffer_B;
			params.nextFrameBuffer = frameBuffer_A;
			usedTexture = textureBuffer_B;


			frameBuffer_B->Unbind();
		}

		currentEffect->BeforeRender(params);
		Draw(*postProcessingVA, *postProcessingIB, *currentEffect->GetShader());
		currentEffect->AfterRender(params);
	}
}

void Renderer::InitializePostProcessing()
{
	// ----------------------------------------------------------------------------- //

	float vertices[] = {
		// Positions
		-1.0f, -1.0f, 0.0f, 0.0f, // Bottom-left
		 1.0f, -1.0f, 1.0f, 0.0f, // Bottom-right
		 1.0f,  1.0f, 1.0f, 1.0f, // Top-right
		-1.0f,  1.0f, 0.0f, 1.0f  // Top-left
	};
	GLuint indices[] = {
		0, 1, 2,
		2, 3, 0
	};

	VertexBuffer* vb = new VertexBuffer(sizeof(vertices) * 4, &vertices[0]);

	VertexBufferLayout layout;
	layout.Push<float>(2);
	layout.Push<float>(2);
	postProcessingVA = new VertexArray;
	postProcessingVA->AddBuffer(*vb, layout);
	postProcessingIB = new IndexBuffer;
	postProcessingIB = new IndexBuffer(&indices[0], sizeof(indices));

	// ----------------------------------------------------------------------------- //

	baseFBO = new FrameBuffer(GL_FRAMEBUFFER);

	baseTexture = new TextureBuffer(GL_TEXTURE_2D, RESOLUTION.x, RESOLUTION.y);
	baseTexture->Unbind();

	baseTexture->AttachToFrameBuffer(GL_FRAMEBUFFER);

	renderBuffer = new RenderBuffer(RESOLUTION.x, RESOLUTION.y);
	renderBuffer->Unbind();
	renderBuffer->AttachToFrameBuffer(GL_FRAMEBUFFER);

	depthTexture_A = new TextureBuffer(
		GL_TEXTURE_2D,
		RESOLUTION.x,
		RESOLUTION.y,
		true);

	depthTexture_A->Unbind();
	depthTexture_A->AttachToFrameBuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT);

	baseFBO->CheckStatus();

	// ----------------------------------------------------------------------------- //

	frameBuffer_A = new FrameBuffer(GL_FRAMEBUFFER);

	textureBuffer_A = new TextureBuffer(GL_TEXTURE_2D, RESOLUTION.x, RESOLUTION.y);
	textureBuffer_A->Unbind();
	textureBuffer_A->AttachToFrameBuffer(GL_FRAMEBUFFER);

	frameBuffer_A->CheckStatus();

	// ----------------------------------------------------------------------------- //

	frameBuffer_B = new FrameBuffer(GL_FRAMEBUFFER);

	textureBuffer_B = new TextureBuffer(GL_TEXTURE_2D, RESOLUTION.x, RESOLUTION.y);
	textureBuffer_B->Unbind();
	textureBuffer_B->AttachToFrameBuffer(GL_FRAMEBUFFER);

	depthTexture_B = new TextureBuffer(
		GL_TEXTURE_2D,
		RESOLUTION.x,
		RESOLUTION.y,
		true);

	depthTexture_B->Unbind();
	depthTexture_B->AttachToFrameBuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT);

	frameBuffer_B->CheckStatus();

	// ----------------------------------------------------------------------------- //

	screenShader = new Shader(SHADERPATH + "HDR.vert", SHADERPATH + "HDR.frag");
	screenShaderHor = new Shader(SHADERPATH + "HorizontalSS.vert", SHADERPATH + "HorizontalSS.frag");
	screenShaderVert = new Shader(SHADERPATH + "VerticalSS.vert", SHADERPATH + "VerticalSS.frag");

	// ----------------------------------------------------------------------------- //

	std::vector<float> gausianKernelHor = { 2.0f, 4.0f, 2.0f };

	std::vector<glm::vec2> gausianKernelOffsetsHor = {
		glm::vec2((1.0f / RESOLUTION.x), 0.0f),
		glm::vec2(0.0f,  0.0f),
		glm::vec2(-(1.0f / RESOLUTION.x), 0.0f)
	};

	auto gausianHor = PostProcessingFactory::GetKnownEffect("GaussianBlurPassHorizontal");

	gausianHor->UpdateShader(screenShaderHor);
	gausianHor->UpdateKernel(gausianKernelHor);
	gausianHor->UpdateKernelOffsets(gausianKernelOffsetsHor);

	PostProcessingFactory instance = PostProcessingFactory::getInstance();

	instance.AddToQueue(gausianHor);

	std::vector<float> gausianKernelVert = { 2.0f, 4.0f, 2.0f };

	std::vector<glm::vec2> gausianKernelOffsetsVert = {
		glm::vec2(0.0f,  (1.0f / RESOLUTION.y)),
		glm::vec2(0.0f,  0.0f),
		glm::vec2(0.0f, -(1.0f / RESOLUTION.y))
	};


	auto gausianVert = PostProcessingFactory::GetKnownEffect("GaussianBlurPassVertical");

	gausianVert->UpdateShader(screenShaderHor);
	gausianVert->UpdateKernel(gausianKernelVert);
	gausianVert->UpdateKernelOffsets(gausianKernelOffsetsVert);

	auto HDR = PostProcessingFactory::GetKnownEffect("HDRPass");

	HDR->UpdateShader(screenShader);
	instance.AddToQueue(HDR, 0);
	instance.AddPingPongToQueue(gausianHor, gausianVert, 20, 1);
}

void Renderer::Draw(Scene* scene, GameObject* go, bool recursive) const
{
	std::vector<RenderObject*> renderObjects = go->GetRenderObjects();

	for (int i = 0; i < renderObjects.size(); i++) {

		Draw(scene, *renderObjects[i], go->GetTransform(), camera->GetViewMatrix(), projection);
	}

	if (!recursive)
		return;

	std::vector<GameObject*> children = go->GetChildren();

	for (int i = 0; i < children.size(); i++)
	{
		if (children[i]->ChildCount() > 0)
			Draw(scene, children[i], true);
		else
			Draw(scene, children[i]);
	}
}

void Renderer::Draw(Scene* scene, RenderObject& ro, glm::mat4 model, glm::mat4 view, glm::mat4 projection) const
{
	Material* mat = ro.GetMaterial();
	Mesh* mesh = ro.GetMesh();

	mat->Render(model, view, projection, scene);
	Draw(*ro.GetMesh(), *mat->shader);

	scene->GetLightsBuffer()->Unbind();
}

void Renderer::Clear()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::SetActiveCamera(Camera* camera)
{
	this->camera = camera;
}
