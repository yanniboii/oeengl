#pragma once
#include <iostream>;
#include <vector>
#include "Mesh.h"
#include "Material.h"

class GameObject {
public:
	GameObject();
	~GameObject();

	void AddChild(GameObject child);
	//std::vector<RenderObject> GetRenderObjects() { return renderObjects; };

	std::vector<GameObject> GetChildren() { return children; };
private:
	std::string name;
	GameObject* parent;
	std::vector<GameObject> children;
	//std::vector<RenderObject> renderObjects;
};

class RenderObject {
public:
	RenderObject(Mesh* mesh, Material* mat) :mesh(mesh), mat(mat) {}
	~RenderObject() {}

	inline Mesh& GetMesh() { return *mesh; }
	inline Material& GetMaterial() { return *mat; }
private:
	Mesh* mesh;
	Material* mat;
};