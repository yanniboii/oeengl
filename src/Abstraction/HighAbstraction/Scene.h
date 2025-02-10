#pragma once
#include "GameObject.h"
#include "Light.h"


class Scene :public GameObject {
public:
	Scene() {};
	~Scene() {};

	void AddLight(Light* light) { lights.push_back(light); };
	std::vector<Light*> GetLights() { return lights; };

private:
	std::vector<Light*> lights;
};