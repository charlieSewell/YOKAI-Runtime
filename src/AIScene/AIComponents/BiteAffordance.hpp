#pragma once

#include "IAffordance.hpp"
#include <glm/glm.hpp>
#include <memory>
#include <functional>
#include "Transform.hpp"
#include "Components/BoxCollider.hpp"
#include "AIScene/AIComponents/EmotionSystem.hpp"

class BiteAffordance : public IAffordance
{
public:

	BiteAffordance() = default;

	void Update(float deltaTime) override;

	void EnableAbility(std::shared_ptr<EmotionSystem> emotionSystem);
	void EnableAffordance(std::function<glm::vec3()> getPosition, std::shared_ptr<EmotionSystem> emotionSystem);

	void Interact(std::shared_ptr<BiteAffordance> other);
	void Stop();

	std::function<glm::vec3()> GetPosition;

	std::shared_ptr<EmotionSystem> m_emotionSystemPtr = nullptr;
private:

	std::shared_ptr<BiteAffordance> m_otherBiteAffordance = nullptr;

};