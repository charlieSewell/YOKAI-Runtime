#include "PLayerScript.hpp"

PlayerScript::PlayerScript(GameObject* parent)
	: 
	Component(parent),
	gameObject(parent),
	camera(gameObject->AddComponent<Camera>()),
	input(gameObject->AddComponent<Input>())

{
	Awake();
}

void PlayerScript::Awake()
{
	movementSpeed = 0.01f;
	lookSensitivity = 0.05f;
	sprintMultiplyer = 4;
}

void PlayerScript::Start()
{

}

void PlayerScript::Update(float deltaTime)
{
	UpdateMovement();
}

void PlayerScript::Draw()
{

}

void PlayerScript::UpdateMovement()
{
	if(input->GetKeyState('w'))
		camera->m_position += glm::vec3(camera->m_frontDirection.x, 0, camera->m_frontDirection.z) * movementSpeed;

	if (input->GetKeyState('s'))
		camera->m_position -= glm::vec3(camera->m_frontDirection.x, 0, camera->m_frontDirection.z) * movementSpeed;

	if (input->GetKeyState('a'))
		camera->m_position -= glm::normalize(glm::cross(camera->m_frontDirection, camera->m_upDirection)) * movementSpeed;

	if (input->GetKeyState('p'))
		camera->m_position += glm::normalize(glm::cross(camera->m_frontDirection, camera->m_upDirection)) * movementSpeed;

	if (input->GetKeyState(' '))
		camera->m_position += camera->m_upDirection * movementSpeed;

	if (input->GetKeyState(SPECIAL::LEFT_CONTROL))
		camera->m_position -= camera->m_upDirection * movementSpeed;

	if (input->GetKeyState(SPECIAL::LEFT_SHIFT))
	{
		if(!sprintActive)
			movementSpeed *= sprintMultiplyer;

		sprintActive = true;
	}
	else
	{
		if (sprintActive)
			movementSpeed /= sprintMultiplyer;

		sprintActive = false;
	}
		


	yaw += input->GetMouseState().offset.x * lookSensitivity;
	pitch -= input->GetMouseState().offset.y * lookSensitivity;

	// stops bad weird camera movement
	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;

	glm::vec3 direction;
	direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	direction.y = sin(glm::radians(pitch));
	direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	camera->m_frontDirection = glm::normalize(direction);
}