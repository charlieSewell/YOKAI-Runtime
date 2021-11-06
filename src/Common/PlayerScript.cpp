#include "PlayerScript.hpp"

PlayerScript::PlayerScript(GameObject* parent)
	:
	Component(parent),
	gameObject(parent),
	transform(gameObject->AddComponent<Transform>()),
	camera(gameObject->AddComponent<Camera>()),
	input(gameObject->AddComponent<Input>()),
	sphereCollider(gameObject->AddComponent<SphereCollider>()){}

void PlayerScript::Awake()
{
	movementSpeed = 0.05f;
	lookSensitivity = 0.05f;
	sprintMultiplyer = 4;
	std::function<glm::vec3()> getPlayerPosition = [&]() { return transform->GetPosition(); };
	std::function<glm::vec3()> getPlayerDirection = [&]() { return camera->m_frontDirection; };
}

void PlayerScript::Start()
{
	//sphereCollider->Start();
	///*
	//sphereCollider->SetLinearVelocity(glm::dvec3(0, 0, 0));
	//sphereCollider->SetAngularVelocity(glm::dvec3(0, 0, 0));
	//sphereCollider->SetMass(2.0);
	//sphereCollider->SetIsStaticObject(false);
	//sphereCollider->SetInertiaTensor();
	//sphereCollider->SetOrientation(glm::quat(1, 0, 0, 0));
	//sphereCollider->SetGravityAffected(true);
	//*/
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
	glm::vec3 tempPosition = glm::vec3(0, 0, 0);

	if(input->GetKeyState(YOKAI_INPUT::W))
		tempPosition += glm::vec3(camera->m_frontDirection.x, 0, camera->m_frontDirection.z) * movementSpeed;

	if (input->GetKeyState(YOKAI_INPUT::S))
		tempPosition -= glm::vec3(camera->m_frontDirection.x, 0, camera->m_frontDirection.z) * movementSpeed;

	if (input->GetKeyState(YOKAI_INPUT::A))
		tempPosition -= glm::normalize(glm::cross(camera->m_frontDirection, camera->m_upDirection)) * movementSpeed;

	if (input->GetKeyState(YOKAI_INPUT::D))
		tempPosition += glm::normalize(glm::cross(camera->m_frontDirection, camera->m_upDirection)) * movementSpeed;

	if (input->GetKeyState(YOKAI_INPUT::SPACE))
		tempPosition += camera->m_upDirection * movementSpeed;

	if (input->GetKeyState(YOKAI_INPUT::LEFT_CONTROL))
		tempPosition -= camera->m_upDirection * movementSpeed;

	if (input->GetKeyState(YOKAI_INPUT::LEFT_SHIFT))
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

	transform->SetPosition(transform->GetPosition() + tempPosition);

	if(!m_pauseMouse)
	{
		yaw += input->GetMouseState().offset.x * lookSensitivity;
		pitch -= input->GetMouseState().offset.y * lookSensitivity;

		// stops bad weird camera movement
		if (pitch > 89.0f)
			pitch = 89.0f;
		if (pitch < -89.0f)
			pitch = -89.0f;
	}
	

	glm::vec3 direction;
	direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	direction.y = sin(glm::radians(pitch));
	direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	camera->m_frontDirection = glm::normalize(direction);

	sphereCollider->SetPosition(transform->GetPosition());

}

void PlayerScript::ToggleMouse()
{
	m_pauseMouse = !m_pauseMouse;
	if(m_pauseMouse)
	{
		input->ShowMouse();	
	}
	else
	{
		input->HideMouse();
	}
}