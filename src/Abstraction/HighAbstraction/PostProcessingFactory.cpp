#include "PostProcessingFactory.h"

std::vector<std::shared_ptr<PostProcessing>> PostProcessingFactory::postProcessingQueue;

void PostProcessingFactory::AddToQueue(std::shared_ptr<PostProcessing> pp) {
	postProcessingQueue.push_back(pp);
}

void PostProcessingFactory::AddToQueue(std::shared_ptr<PostProcessing> pp, unsigned int position) {
	CheckOutOfRangeVector(postProcessingQueue.size(), position);
	postProcessingQueue.insert(postProcessingQueue.begin() + position, pp);
}

void PostProcessingFactory::AddPingPongToQueue(std::shared_ptr<PostProcessing> effect_1,
	std::shared_ptr<PostProcessing> effect_2,
	unsigned int pingPongAmount)
{
	for (int i = 0; i < pingPongAmount; i++) {
		postProcessingQueue.push_back(effect_1);
		postProcessingQueue.push_back(effect_2);
	}
}

void PostProcessingFactory::AddPingPongToQueue(std::shared_ptr<PostProcessing> effect_1,
	std::shared_ptr<PostProcessing> effect_2,
	unsigned int pingPongAmount,
	unsigned int position)
{
	CheckOutOfRangeVector(postProcessingQueue.size(), position);
	for (int i = 0; i < pingPongAmount; i++) {
		postProcessingQueue.insert(postProcessingQueue.begin() + position + i, effect_1);
		postProcessingQueue.insert(postProcessingQueue.begin() + position + i + 1, effect_2);
	}
}

void PostProcessingFactory::MoveItemInQueue(unsigned int from, unsigned int to) {
	CheckOutOfRangeVector(postProcessingQueue.size(), from);
	CheckOutOfRangeVector(postProcessingQueue.size(), to);

	std::shared_ptr<PostProcessing> item = postProcessingQueue[from];
	postProcessingQueue.erase(postProcessingQueue.begin() + from);

	if (to > from) --to;

	postProcessingQueue.insert(postProcessingQueue.begin() + to, item);
}

std::shared_ptr<PostProcessing> PostProcessingFactory::GetItemAtPostion(unsigned int position)
{
	CheckOutOfRangeVector(postProcessingQueue.size(), position);
	return postProcessingQueue.at(position);
}

void PostProcessingFactory::RemoveFromQueue(std::shared_ptr<PostProcessing> pp) {
	auto it = std::find(postProcessingQueue.begin(), postProcessingQueue.end(), pp);

	if (it != postProcessingQueue.end()) {
		postProcessingQueue.erase(it);
	}
}

void PostProcessingFactory::RemoveFromQueue(unsigned int position) {
	CheckOutOfRangeVector(postProcessingQueue.size(), position);
	postProcessingQueue.erase(postProcessingQueue.begin() + position);
}

std::vector<std::shared_ptr<PostProcessing>> PostProcessingFactory::GetPostProcessingQueue()
{
	return postProcessingQueue;
}

void PostProcessingFactory::AddToKnownEffects(std::string name, std::shared_ptr<PostProcessing> effect)
{
	int counter = 0;
	std::string originalName = name;

	auto& knownEffects = GetKnownEffectsMap();

	while (knownEffects.find(name) != knownEffects.end()) {
		name = originalName + std::to_string(counter++);
	}

	knownEffects[name] = effect;
}

std::shared_ptr<PostProcessing> PostProcessingFactory::GetKnownEffect(std::string name)
{
	auto& knownEffects = GetKnownEffectsMap();

	if (knownEffects.find(name) == knownEffects.end()) throw std::runtime_error("effect name not found");
	return knownEffects[name];
}

