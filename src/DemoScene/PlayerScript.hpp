#pragma once

#include "Model/GameObject.hpp"
#include "Model/Components/Transform.hpp"
#include "Model/Component.hpp"
#include "Model/Components/Camera.hpp"
#include "Model/Components/SphereCollider.hpp"
#include "Controller/InputComponent.hpp"
#include "Model/Components/ConcaveCollider.hpp"

class GameObject;

class PlayerScript : public Component
{
public:
	PlayerScript(GameObject* parent);
	void Awake();
	void Start();
	void Update(float deltaTime);
	void Draw();

	glm::vec3 Test;

private:
	GameObject* gameObject;
	std::shared_ptr<Transform> transform;
	std::shared_ptr<Camera> camera;
	std::shared_ptr<Input> input;
	std::shared_ptr<SphereCollider> sphereCollider;

	float movementSpeed = 0;
	float lookSensitivity =	0;
	float sprintMultiplyer = 0;
	bool sprintActive = false;

	//TEMP THIS DOES NOT LIVE HERE
	double yaw = -90.0f;
	double pitch = 0.0f;
	double xoffset = 0;
	double yoffset = 0;

	void UpdateMovement();
};