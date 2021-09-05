#pragma once

#include "Model/GameObject.hpp"
#include "Model/Component.hpp"
#include "Model/Components/PlayerControlledMotion.hpp"
#include "Model/Components/Camera.hpp"
#include "Controller/InputComponent.hpp"

class GameObject;

class PlayerScript : public Component
{
public:
	PlayerScript(GameObject* parent);
	void Awake();
	void Start();
	void Update(float deltaTime);
	void Draw();

private:
	GameObject* gameObject;
	std::shared_ptr<PlayerControlledMotion> playerControlledMotion;
	std::shared_ptr<Camera> camera;
	std::shared_ptr<Input> input;

	float movementSpeed = 0;
	float lookSensitivity = 0;

	void UpdateMovement();
};