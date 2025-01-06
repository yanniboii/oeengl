#pragma once
#include "Mesh.h"
#include "Material.h"

class Model {
public:
	void SetMesh(Mesh mesh);
	void SetMaterial(Material material);
private:
	Mesh mesh;
	Material material;
};