#include "PickupAffordance.hpp"

PickupAffordance::PickupAffordance()
{

}

void PickupAffordance::EnableAbility(std::function<glm::vec3()> getPosition, std::function<glm::vec3()> getDirection)
{
	GetPosition = getPosition;
	GetDirection = getDirection;
	HasAbility = true;
}

void PickupAffordance::EnableAffordance(std::function<void(glm::vec3)> setPosition)
{
	SetPosition = setPosition;
	HasAffordance = true;
	IsAvailable = true;
}

void PickupAffordance::Interact(std::shared_ptr<PickupAffordance> other)
{
	other->IsAvailable = false;
	IsActive = true;
	other->SetPosition(GetPosition() + GetDirection() * PickUpOffset);
	other->Afford();
}
 
void PickupAffordance::Afford()
{

}