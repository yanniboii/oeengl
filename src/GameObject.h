#pragma once
#include <iostream>
#include <vector>
#include "RenderObject.h"

class RenderObject;

class GameObject {
public:
	GameObject() {};
	GameObject(glm::mat4 transform) :transform(transform) {};
	~GameObject();

	void AddChild(GameObject* child) { children.push_back(child); }

	std::vector<RenderObject*> GetRenderObjects() { return renderObjects; };

	std::vector<GameObject*>& GetChildren() { return children; };

	int ChildCount() { return children.size(); };

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
