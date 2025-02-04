#pragma once
#include <iostream>
#include <vector>
#include "Mesh.h"
#include "Material.h"

class RenderObject;

class GameObject {
public:
	GameObject(glm::mat4 transform) :transform(transform) {};
	~GameObject();

	void AddChild(GameObject* child) { children.push_back(child); }

	std::vector<RenderObject*> GetRenderObjects() { return renderObjects; };

	std::vector<GameObject*>& GetChildren() { return children; };

	void AddRenderObject(RenderObject* ro) { renderObjects.push_back(ro); };

	void SetPosition(glm::vec3 position)
	{
		transform[3][0] = position[0];
		transform[3][1] = position[1];
		transform[3][2] = position[2];
	};

	glm::mat4 GetTransform() { return transform; };

private:
	std::string name;
	GameObject* parent = nullptr;;
	glm::mat4 transform;
	std::vector<GameObject*> children;
	std::vector<RenderObject*> renderObjects;
};

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