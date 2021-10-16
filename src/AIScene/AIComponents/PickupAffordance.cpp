#include "PickupAffordance.hpp"

PickupAffordance::PickupAffordance()
{

}

void PickupAffordance::EnableAbility(std::function<glm::vec3()> getPosition, std::function<glm::vec3()> getDirection)
{
	m_getPosition = getPosition;
	m_getDirection = getDirection;
	HasAbility = true;
}

void PickupAffordance::EnableAffordance(std::function<void(glm::vec3)> setPosition)
{
	m_setPosition = setPosition;
	HasAffordance = true;
	IsAvailable = true;
}

void PickupAffordance::Interact(std::shared_ptr<PickupAffordance> other)
{
	other->IsAvailable = false;
	other->IsActive = true;
	other->m_setPosition(m_getPosition() + m_getDirection() * 5.0f);
	other->Afford();
}

void PickupAffordance::Afford()
{

}