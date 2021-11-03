#pragma once

#include "Engine/GameObject.hpp"
#include "Components/Transform.hpp"
#include "Components/Component.hpp"
#include "Components/Camera.hpp"
#include "Components/SphereCollider.hpp"
#include "Components/InputComponent.hpp"
#include "Components/ConcaveCollider.hpp"
#include "Components/RayCaster.hpp"
#include "AIScene/AIComponents/AffordanceSystem.hpp"
#include "AIScene/AIComponents/EmotionSystem.hpp"
#include "Renderer/Renderer.hpp"


class GameObject;

class PlayerScript : public Component
{
public:
	PlayerScript(GameObject* parent);
	void Awake() override;
	void Start() override;
	void Update(float deltaTime) override;
	void Draw() override;
	void ToggleMouse();
	std::function<std::shared_ptr<GameObject>(int)> GetAISceneObject;

	void PlayerScript::DrawText(std::string text);

	float movementSpeed = 0;

private:
	GameObject* gameObject;
	std::shared_ptr<Transform> transform;
	std::shared_ptr<Camera> camera;
	std::shared_ptr<Input> input;
	std::shared_ptr<SphereCollider> sphereCollider;
	std::shared_ptr<RayCaster> rayCaster;
	std::shared_ptr<AffordanceSystem> affordanceSystem;

	std::shared_ptr<EmotionSystem> m_emotionSystem;

	float lookSensitivity =	0;
	float sprintMultiplyer = 0;
	bool sprintActive = false;

	//TEMP THIS DOES NOT LIVE HERE
	double yaw = -90.0f;
	double pitch = 0.0f;
	double xoffset = 0;
	double yoffset = 0;
	bool m_pauseMouse = false;
	void UpdateMovement();
	void CheckPickup(std::shared_ptr<GameObject> otherObject);
	void TestEmotions(std::shared_ptr<GameObject> otherObject);
};