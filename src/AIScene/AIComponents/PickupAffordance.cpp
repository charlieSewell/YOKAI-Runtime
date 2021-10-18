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
	m_otherPickupAffordance = other;
	m_otherPickupAffordance->IsAvailable = false;
	IsActive = true;
}
 
void PickupAffordance::Stop()
{
	IsActive = false;
	m_otherPickupAffordance->IsAvailable = true;
	m_otherPickupAffordance = nullptr;
}

void PickupAffordance::Update(float deltaTime)
{
	if(IsActive)
	{
		m_otherPickupAffordance->SetPosition(GetPosition() + GetDirection() * PickUpOffset);
	}
}