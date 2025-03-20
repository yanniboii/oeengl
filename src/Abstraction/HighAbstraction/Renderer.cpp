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
	if (postProcessing != None) {
		frameBuffer_A->Bind();
		renderBuffer->Bind();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glEnable(GL_DEPTH_TEST);
	}

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

	if (postProcessing == Normal) {
		renderBuffer->Unbind();
		frameBuffer_A->Unbind();
		textureBuffer_A->Bind();

		glDisable(GL_DEPTH_TEST);

		Draw(*postProcessingVA, *postProcessingIB, *screenShader);


		frameBuffer_A->Unbind();
	}

	if (postProcessing == PingPong)
	{
		glDisable(GL_DEPTH_TEST);
		renderBuffer->Bind();
		for (int i = 0; i < pingPongAmount; i++) {
			if (i == pingPongAmount - 1) {
				frameBuffer_A->Unbind();
				frameBuffer_B->Unbind();

				screenShaderVert->Use();

				textureBuffer_B->Bind();

				Draw(*postProcessingVA, *postProcessingIB, *screenShaderVert);
			}
			else
			{
				if (i % 2 == 0) {
					screenShaderHor->Use();
					frameBuffer_B->Bind();

					textureBuffer_A->Bind();

					Draw(*postProcessingVA, *postProcessingIB, *screenShaderHor);
				}
				else
				{
					screenShaderVert->Use();
					frameBuffer_A->Bind();

					textureBuffer_B->Bind();

					Draw(*postProcessingVA, *postProcessingIB, *screenShaderVert);

				}
			}
		}
	}
}


void Renderer::Draw(Mesh& mesh, const Shader& shader) const
{
	Draw(mesh.GetVertexArray(), mesh.GetIndexBuffer(), shader);
}

void Renderer::InitializePostProcessing(PostProcessing postProcessing)
{
	if (postProcessing == None) return;

	this->postProcessing = postProcessing;

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

	frameBuffer_A = new FrameBuffer(GL_FRAMEBUFFER);

	textureBuffer_A = new TextureBuffer(GL_TEXTURE_2D, RESOLUTION.x, RESOLUTION.y);
	textureBuffer_A->Unbind();
	textureBuffer_A->AttachToFrameBuffer(GL_FRAMEBUFFER);

	renderBuffer = new RenderBuffer(RESOLUTION.x, RESOLUTION.y);
	renderBuffer->Unbind();
	renderBuffer->AttachToFrameBuffer(GL_FRAMEBUFFER);

	frameBuffer_A->CheckStatus();

	frameBuffer_B = new FrameBuffer(GL_FRAMEBUFFER);

	textureBuffer_B = new TextureBuffer(GL_TEXTURE_2D, RESOLUTION.x, RESOLUTION.y);
	textureBuffer_B->Unbind();
	textureBuffer_B->AttachToFrameBuffer(GL_FRAMEBUFFER);

	renderBuffer->AttachToFrameBuffer(GL_FRAMEBUFFER);

	frameBuffer_B->CheckStatus();

	screenShader = new Shader(SHADERPATH + "ScreenShader.vert", SHADERPATH + "ScreenShader.frag");
	screenShaderHor = new Shader(SHADERPATH + "HorizontalSS.vert", SHADERPATH + "HorizontalSS.frag");
	screenShaderVert = new Shader(SHADERPATH + "VerticalSS.vert", SHADERPATH + "VerticalSS.frag");
}

void Renderer::Draw(Scene* scene, GameObject* go, bool recursive) const
{
	// TODO: find a better place for this now it is called every time I draw 
	glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)RESOLUTION.x / RESOLUTION.y, 0.1f, 100.0f);

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
