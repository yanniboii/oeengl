#pragma once
#include <memory>
#include <unordered_map>
#include <string>
#include "PostProcessing.h"
#include "../../Misc/Utils.h"
#include "../../assets/Scripts/PostProcessing/GausianBlurPass.h"
#include "../../assets/Scripts/PostProcessing/HDRPass.h"

class PostProcessingFactory {
public:
	static PostProcessingFactory& getInstance() {
		static PostProcessingFactory instance;
		return instance;
	}

	void AddToQueue(std::shared_ptr<PostProcessing> pp);
	void AddToQueue(std::shared_ptr<PostProcessing> pp, unsigned int position);

	void AddPingPongToQueue(std::shared_ptr<PostProcessing> effect_1,
		std::shared_ptr<PostProcessing> effect_2,
		unsigned int pingPongAmount);
	void AddPingPongToQueue(std::shared_ptr<PostProcessing> effect_1,
		std::shared_ptr<PostProcessing> effect_2,
		unsigned int pingPongAmount,
		unsigned int position);

	void MoveItemInQueue(unsigned int from, unsigned int to);

	std::shared_ptr<PostProcessing> GetItemAtPostion(unsigned int position);

	void RemoveFromQueue(std::shared_ptr<PostProcessing> pp);
	void RemoveFromQueue(unsigned int position);

	std::vector<std::shared_ptr<PostProcessing>> GetPostProcessingQueue();

	static void AddToKnownEffects(std::string name, std::shared_ptr<PostProcessing> effect);
	static std::shared_ptr<PostProcessing> GetKnownEffect(std::string name);

private:
	static std::vector<std::shared_ptr<PostProcessing>> postProcessingQueue;
	static std::unordered_map<std::string, std::shared_ptr<PostProcessing>>& GetKnownEffectsMap() {
		static std::unordered_map<std::string, std::shared_ptr<PostProcessing>> knownEffects;
		return knownEffects;
	}
};

#define REGISTER_POSTPROCESSING_EFFECT(classname, name) \
namespace { \
\
	std::shared_ptr<PostProcessing> Create##classname##_##name(){ \
		return std::make_shared<classname>(); \
	} \
	struct classname##Registrar_##name{ \
		classname##Registrar_##name() { \
			PostProcessingFactory::AddToKnownEffects(#name, Create##classname##_##name()); \
		} \
	}; \
	static classname##Registrar_##name global_##classname##Registrar_##name; \
}
