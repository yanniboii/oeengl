#pragma once
#include "Mesh.h"
#include "Material.h"


class RenderObject {
public:
	RenderObject(Mesh* mesh, Material* mat) :mesh(mesh), mat(mat) {}
	~RenderObject() {}

	inline Mesh* GetMesh() { return mesh; }
	inline Material* GetMaterial() { return mat; }
private:
	Mesh* mesh;
	Material* mat;
};
