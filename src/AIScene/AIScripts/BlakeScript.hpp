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
#include "../AIComponents/EmotionSystem.hpp"
#include "../AIComponents/PickupAffordance.hpp"

class GameObject;

class BlakeScript : public Component
{
public:
	BlakeScript(GameObject* parent);
	void Awake();
	void Start();
	void Update(float deltaTime);
	void Draw();

	std::function<std::shared_ptr<GameObject>(int)> GetAISceneObject;

private:
	GameObject* gameObject;
	std::shared_ptr<Transform> transform;
	std::shared_ptr<SphereCollider> sphereCollider;
	std::shared_ptr<RayCaster> rayCaster;
	std::shared_ptr<AutomatedBehaviours> automatedBehaviours;
	std::shared_ptr<EmotionSystem> emotionSystem;
	std::shared_ptr<AffordanceSystem> affordanceSystem;

	bool CheckPickup(std::shared_ptr<GameObject> otherObject);
};