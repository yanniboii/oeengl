#pragma once
#include <iostream>
#include <vector>
#include "RenderObject.h"

class GameObject {
public:
	GameObject() :transform(glm::mat4(1.0f)) {};
	GameObject(glm::mat4 transform) :transform(transform) {};
	~GameObject() {};

	virtual void AddChild(GameObject* child) { children.push_back(child); };

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

	void Translate(glm::vec3 translation)
	{
		transform[3][0] += translation[0];
		transform[3][1] += translation[1];
		transform[3][2] += translation[2];
	}

	glm::vec3 GetPosition() { return transform[3]; };

	glm::mat4 GetTransform() { return transform; };

protected:
	std::string name;
	std::vector<GameObject*> children;
	glm::mat4 transform;
private:
	GameObject* parent = nullptr;;
	std::vector<RenderObject*> renderObjects;
};
