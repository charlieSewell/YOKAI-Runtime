#include "PickupAffordance.hpp"

#include "glm/gtc/matrix_transform.hpp"

void PickupAffordance::EnableAbility(std::function<glm::vec3()> getPosition, std::function<glm::vec3()> getDirection)
{
	GetPosition = getPosition;
	GetDirection = getDirection;
	HasAbility = true;
}

void PickupAffordance::EnableAffordance(std::shared_ptr<Transform> transform)
{
	//SetTransform = setTransform;
	transformPtr = transform;
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
		Transform transform = glm::inverse(glm::lookAt(GetPosition(), GetPosition() + GetDirection(), glm::vec3(0, 1, 0)));
		glm::vec3 offset = GetDirection() * PickupFrontOffset;
		offset.y += PickupHeightOffset;
		transform.setPosition(GetPosition() + offset);
		transform.setScale(m_otherPickupAffordance->transformPtr->getScale());
		*m_otherPickupAffordance->transformPtr = transform;
	}
}