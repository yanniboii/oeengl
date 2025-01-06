#pragma once
#include <vector>
#include <glm/glm.hpp>
#include <iostream>
#include <algorithm>
#include "VertexArray.h"
#include "IndexBuffer.h"

using namespace glm;
using namespace std;

struct Vertex {
	fvec3 postion = glm::fvec3(0, 0, 0);
	fvec3 colors = glm::fvec3(0 ,0, 0);
	fvec3 normals = glm::fvec3(0, 0, 0);
	fvec2 uvs = glm::fvec2(0, 0);
};

struct Face {
	vector<unsigned int> indeces;
};

class Mesh {
public:
	Mesh(const vector<Vertex>& vertices = {})
		: vertices(vertices) {}

	inline const vector<Vertex>& GetVertices() const { return vertices; }

	inline const vector<fvec3>& GetPos() const { return position; }
	inline const vector<fvec3>& GetNormals() const { return normals; }

	vector<unsigned int> GetFaces() const 
	{ 
		std::vector<unsigned int> indeces;

		for (const auto& face : faces) 
		{
			indeces.insert(indeces.end(), face.indeces.begin(), face.indeces.end());
		}		

		return indeces;
	}
	inline const vector<unsigned int>& GetFace(int index) const { return faces.at(index).indeces; }

	void AddVertex(const Vertex& vertex) { vertices.push_back(vertex); }

	void AddPos(const fvec3 vertex) { position.push_back(vertex); }

	void AddNorm(const fvec3 vertex) { normals.push_back(vertex); }
	//void AddPos(const fvec3 vertex) { position.push_back(vertex); }
	
	inline const void AddFace(Face t) { faces.push_back(t); }

	const void AddFaces(const vector<Face>& faces) 
	{ 
		this->faces.insert(
			this->faces.end(),
			faces.begin(),
			faces.end()); 
	}

	inline const void SetVertices(const vector<Vertex>& vertices) { this->vertices = vertices; }
	inline const void SetFaces(const vector<Face>& faces) { this->faces = faces; }

	//void SetVertexArray(VertexArray va) { this->va = va; }
	//void SetIndexBuffer(IndexBuffer ib) { this->ib = ib; }

	//inline const VertexArray GetVertexArray() { return va; }
	//inline const IndexBuffer GetIndexBuffer() { return ib; }

private:
	vector<Vertex> vertices;
	vector <fvec3> position;
	vector <fvec3> normals;
	vector <fvec3> colors;
	vector <fvec2> uvs;
	vector<Face> faces;

	//VertexArray va;
	//IndexBuffer ib;
};