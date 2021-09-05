#include "PLayerScript.hpp"

PlayerScript::PlayerScript(GameObject* parent)
	: 
	Component(parent),
	gameObject(parent),
	camera(gameObject->AddComponent<Camera>()),
	playerControlledMotion(gameObject->AddComponent<PlayerControlledMotion>()),
	input(gameObject->AddComponent<Input>())

{
	Awake();
}

void PlayerScript::Awake()
{
	movementSpeed = 0.01f;
	lookSensitivity = 0.05f;
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

	if (input->GetKeyState('d'))
		camera->m_position += glm::normalize(glm::cross(camera->m_frontDirection, camera->m_upDirection)) * movementSpeed;

	if (input->GetKeyState(' '))
		camera->m_position += camera->m_upDirection * movementSpeed;

	if (input->GetKeyState('c'))
		camera->m_position -= camera->m_upDirection * movementSpeed;

	static double xoffset = input->GetMouseOffset().x;
	static double yoffset = input->GetMouseOffset().y;

	double yaw = -90.0f;
	double pitch = 0.0f;

	xoffset *= lookSensitivity;
	yoffset *= lookSensitivity;

	yaw += xoffset;
	pitch -= yoffset;

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