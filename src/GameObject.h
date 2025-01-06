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
	RenderObject();
	~RenderObject();
private:
	Mesh mesh;
	Material mat;
};