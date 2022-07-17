#pragma once

#include "IAffordance.hpp"
#include <glm/glm.hpp>
#include <memory>
#include <functional>
#include "Transform.hpp"
#include "Components/BoxCollider.hpp"

class PickupAffordance : public IAffordance
{
public:

	PickupAffordance() = default;

	void Update(float deltaTime) override;

	void EnableAbility(std::function<glm::vec3()> getPosition, std::function<glm::vec3()> getDirection);
	void EnableAffordance(std::shared_ptr<Transform> transform, std::shared_ptr<BoxCollider> boxCollider);

	void Interact(std::shared_ptr<PickupAffordance> other);
	void Stop();

	std::function<glm::vec3()> GetPosition;
	std::function<glm::vec3()> GetDirection;
	std::function<void(Transform)> SetTransform;

	float PickupFrontOffset = 2.0f;	// The distance in front of the actor the object is placed
	float PickupHeightOffset = 0.0f;

	std::shared_ptr<Transform> transformPtr = nullptr;
	std::shared_ptr<BoxCollider> colliderPtr = nullptr;
	bool isDynamic = false;

private:

	std::shared_ptr<PickupAffordance> m_otherPickupAffordance = nullptr;

};