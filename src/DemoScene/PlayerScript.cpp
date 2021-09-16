#include "PlayerScript.hpp"

PlayerScript::PlayerScript(GameObject* parent)
	:
	Component(parent),
	gameObject(parent),
	transform(gameObject->AddComponent<Transform>()),
	camera(gameObject->AddComponent<Camera>()),
	input(gameObject->AddComponent<Input>()),
	sphereCollider(gameObject->AddComponent<SphereCollider>())
{
	Awake();
}


void PlayerScript::Awake()
{
	
	movementSpeed = 3.05f;
	lookSensitivity = 0.05f;
	sprintMultiplyer = 4;
}

void PlayerScript::Start()
{
	transform->setPosition(glm::vec3(16, 2, -5));
    
}

void PlayerScript::Update(float deltaTime)
{
	UpdateMovement();
	std::cout << transform->getPosition().x << ", " << transform->getPosition().y << ", " << transform->getPosition().z << "\n";
}

void PlayerScript::Draw()
{

}

void PlayerScript::UpdateMovement()
{
	glm::vec3 tempPosition = glm::vec3(0, 0, 0);

	if(input->GetKeyState('w'))
		tempPosition += glm::vec3(camera->m_frontDirection.x, 0, camera->m_frontDirection.z) * movementSpeed;

	if (input->GetKeyState('s'))
		tempPosition -= glm::vec3(camera->m_frontDirection.x, 0, camera->m_frontDirection.z) * movementSpeed;

	if (input->GetKeyState('a'))
		tempPosition -= glm::normalize(glm::cross(camera->m_frontDirection, camera->m_upDirection)) * movementSpeed;

	if (input->GetKeyState('d'))
		tempPosition += glm::normalize(glm::cross(camera->m_frontDirection, camera->m_upDirection)) * movementSpeed;

	if (input->GetKeyState(' '))
		tempPosition += camera->m_upDirection * movementSpeed;

	if (input->GetKeyState(SPECIAL::LEFT_CONTROL))
		tempPosition -= camera->m_upDirection * movementSpeed;

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

	tempPosition.y -= movementSpeed / 4; //(gravity)
	sphereCollider->NewVelocity = tempPosition;

	camera->m_position = transform->getPosition();
	camera->m_position.y += 0.75;
}