#pragma once
#include "GameObject.h"
#include "../Abstraction/LowAbstraction/ShaderStorageBufferObject.h"


class Scene :public GameObject {
public:
	Scene() { lightsBuffer = new ShaderStorageBufferObject(); };
	~Scene() {};

	void AddLight(Light* light) { lights.push_back(light); };
	std::vector<Light*> GetLights() { return lights; };

	ShaderStorageBufferObject* GetLightsBuffer() { return lightsBuffer; };

private:
	std::vector<Light*> lights;
	ShaderStorageBufferObject* lightsBuffer;
};