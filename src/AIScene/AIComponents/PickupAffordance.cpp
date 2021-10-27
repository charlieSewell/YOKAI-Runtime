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
	transformPtr = transform;
	HasAffordance = true;
}

void PickupAffordance::Interact(std::shared_ptr<PickupAffordance> other)
{
	IsUsing = true;
	m_otherPickupAffordance = other;
	m_otherPickupAffordance->IsAffording = true;
}
 
void PickupAffordance::Stop()
{
	IsUsing = false;
	m_otherPickupAffordance->IsAffording = false;
	m_otherPickupAffordance->transformPtr->setRotation(glm::quat{});
	m_otherPickupAffordance = nullptr;
}

void PickupAffordance::Update(float deltaTime)
{
	if(IsUsing)
	{
		Transform transform = glm::inverse(glm::lookAt(GetPosition(), GetPosition() + GetDirection(), glm::vec3(0, 1, 0)));
		glm::vec3 offset = GetDirection() * PickupFrontOffset;
		offset.y += PickupHeightOffset;
		transform.setPosition(GetPosition() + offset);
		transform.setScale(m_otherPickupAffordance->transformPtr->getScale());
		*m_otherPickupAffordance->transformPtr = transform;
	}
}