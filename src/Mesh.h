#pragma once
#include <vector>
#include <glm/glm.hpp>
#include <iostream>
#include <algorithm>
#include "VertexArray.h"
#include "IndexBuffer.h"

struct Vertex {
	glm::fvec3 postion = glm::fvec3(0, 0, 0);
	glm::fvec3 colors = glm::fvec3(0, 0, 0);
	glm::fvec3 normals = glm::fvec3(0, 0, 0);
	glm::fvec2 uvs = glm::fvec2(0, 0);
};

struct Face {
	std::vector<unsigned int> indeces;
};

class Mesh {
public:
	Mesh(VertexArray& va, IndexBuffer& ib)
		: va(va), ib(ib) {}

	inline const std::vector<Vertex>& GetVertices() const { return vertices; }

	inline const std::vector<glm::fvec3>& GetPos() const { return position; }
	inline const std::vector<glm::fvec3>& GetNormals() const { return normals; }

	inline VertexArray& GetVertexArray() { return va; }
	inline IndexBuffer& GetIndexBuffer() { return ib; }

	std::vector<unsigned int> GetFaces() const
	{
		std::vector<unsigned int> indeces;

		for (const auto& face : faces)
		{
			indeces.insert(indeces.end(), face.indeces.begin(), face.indeces.end());
		}

		return indeces;
	}
	inline const std::vector<unsigned int>& GetFace(int index) const { return faces.at(index).indeces; }

	void AddVertex(const Vertex& vertex) { vertices.push_back(vertex); }

	void AddPos(const glm::fvec3 vertex) { position.push_back(vertex); }

	void AddNorm(const glm::fvec3 vertex) { normals.push_back(vertex); }
	//void AddPos(const fvec3 vertex) { position.push_back(vertex); }

	inline const void AddFace(Face t) { faces.push_back(t); }

	const void AddFaces(const std::vector<Face>& faces)
	{
		this->faces.insert(
			this->faces.end(),
			faces.begin(),
			faces.end());
	}

	inline const void SetVertices(const std::vector<Vertex>& vertices) { this->vertices = vertices; }
	inline const void SetFaces(const std::vector<Face>& faces) { this->faces = faces; }

	//void SetVertexArray(VertexArray va) { this->va = va; }
	//void SetIndexBuffer(IndexBuffer ib) { this->ib = ib; }



private:
	std::vector<Vertex> vertices;
	std::vector <glm::fvec3> position;
	std::vector <glm::fvec3> normals;
	std::vector <glm::fvec3> colors;
	std::vector <glm::fvec2> uvs;
	std::vector<Face> faces;

	VertexArray va;
	IndexBuffer ib;
};