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

	std::function<glm::vec3()> GetPosition;
	std::function<glm::vec3()> GetDirection;
	std::function<void(glm::vec3)> SetPosition;

	float PickUpOffset = 5.0f;	// The distance in front of the actor the object is placed

private:

};