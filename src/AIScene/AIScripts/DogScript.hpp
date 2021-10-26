#pragma once

#include "Engine/GameObject.hpp"
#include "Components/Transform.hpp"
#include "Components/Component.hpp"
#include "Components/SphereCollider.hpp"
#include "Components/InputComponent.hpp"
#include "Components/RayCaster.hpp"
#include "Components/AutomatedBehaviours.hpp"
#include "Components/DrawableEntity.hpp"
#include "../AIComponents/AffordanceSystem.hpp"
#include "../AIComponents/PickupAffordance.hpp"

class GameObject;

class DogScript : public Component
{
public:
	DogScript(GameObject* parent);
	void Awake();
	void Start();
	void Update(float deltaTime);
	void Draw();

	std::function<std::shared_ptr<GameObject>(int)> GetAISceneObject;

private:
	GameObject* m_gameObject;
	std::shared_ptr<Transform> m_transform;
	std::shared_ptr<SphereCollider> m_sphereCollider;
	std::shared_ptr<RayCaster> m_rayCaster;
	std::shared_ptr<AutomatedBehaviours> m_automatedBehaviours;
	std::shared_ptr<AffordanceSystem> m_affordanceSystem;

	bool CheckPickup(std::shared_ptr<GameObject> otherObject);
};