#pragma once

#include "IAffordance.hpp"
#include <glm/glm.hpp>
#include <memory>
#include <functional>

class PickupAffordance : public Affordance
{
public:

	PickupAffordance();

	void EnableAbility(std::function<glm::vec3()> getPosition, std::function<glm::vec3()> getDirection);
	void EnableAffordance(std::function<void(glm::vec3)> setPosition);

	void Interact(std::shared_ptr<PickupAffordance> other);
	void Afford();

//private:

	std::function<glm::vec3()> m_getPosition;
	std::function<glm::vec3()> m_getDirection;
	std::function<void(glm::vec3)> m_setPosition;
};