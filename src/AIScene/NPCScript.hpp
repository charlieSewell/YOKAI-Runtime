#pragma once

#include "Engine/GameObject.hpp"
#include "Components/Transform.hpp"
#include "Components/Component.hpp"
#include "Components/Camera.hpp"
#include "Components/SphereCollider.hpp"
#include "Components/InputComponent.hpp"
#include "Components/ConcaveCollider.hpp"
#include "Components/RayCaster.hpp"
#include "Components/AutomatedBehaviours.hpp"
#include "AIComponents/AffordanceSystem.hpp"
#include "AIComponents/PickupAffordance.hpp"

class GameObject;

class NPCScript : public Component
{
public:
	NPCScript(GameObject* parent);
	void Awake();
	void Start();
	void Update(float deltaTime);
	void Draw();

private:
	GameObject* gameObject;
	std::shared_ptr<Transform> transform;
	std::shared_ptr<SphereCollider> sphereCollider;
	std::shared_ptr<RayCaster> rayCaster;
	std::shared_ptr<AutomatedBehaviours> automatedBehaviours;
	std::shared_ptr<AffordanceSystem> affordanceSystem;
};