#pragma once

#include "Engine/GameObject.hpp"
#include "Components/Transform.hpp"
#include "Components/Component.hpp"
#include "Components/InputComponent.hpp"
#include "Components/BoxCollider.hpp"
#include "Components/DrawableEntity.hpp"
#include "../AIComponents/AffordanceSystem.hpp"
#include "../AIComponents/PickupAffordance.hpp"

class GameObject;

class CubeScript : public Component
{
public:
	CubeScript(GameObject* parent);
	void Awake();
	void Start();
	void Update(float deltaTime);
	void Draw();

private:
	GameObject* m_gameObject;
	std::shared_ptr<Transform> m_transform;
	std::shared_ptr<BoxCollider> m_boxCollider;
	std::shared_ptr<AffordanceSystem> m_affordanceSystem;
};