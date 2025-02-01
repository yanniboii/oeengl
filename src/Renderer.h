#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "GameObject.h"


class Renderer {
public:
	void Draw(const VertexArray& va, const IndexBuffer& ib, const  Shader& shader) const;
	void Draw(const GameObject& go) const;
	void Draw(Mesh& mesh, const Shader& shader) const;
	void Clear();
private:

};