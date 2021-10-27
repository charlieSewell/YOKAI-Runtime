#pragma once

#include "Engine/GameObject.hpp"
#include "Components/Transform.hpp"
#include "Components/Component.hpp"
#include "Components/BoxCollider.hpp"
#include "Components/SphereCollider.hpp"
#include "Components/InputComponent.hpp"
#include "Components/RayCaster.hpp"
#include "Components/AutomatedBehaviours.hpp"
#include "Components/DrawableEntity.hpp"
#include "../AIComponents/AffordanceSystem.hpp"
#include "../AIComponents/EmotionSystem.hpp"

class GameObject;

class ZombieScript : public Component
{
public:
	ZombieScript(GameObject* parent);
	void Awake();
	void Start();
	void Update(float deltaTime);
	void Draw();

	std::function<std::shared_ptr<GameObject>(int)> GetAISceneObject;

private:
	GameObject* m_gameObject;
	std::shared_ptr<Transform> m_transform;
	std::shared_ptr<BoxCollider> m_boxCollider;
	std::shared_ptr<RayCaster> m_rayCaster;
	std::shared_ptr<AutomatedBehaviours> m_automatedBehaviours;
	std::shared_ptr<EmotionSystem> m_emotionSystem;
	std::shared_ptr<AffordanceSystem> m_affordanceSystem;

	float m_topSpeed = 0.005f;

	bool CheckPickup(std::shared_ptr<GameObject> otherObject);
};