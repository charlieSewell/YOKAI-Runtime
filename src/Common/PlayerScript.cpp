#include "PlayerScript.hpp"
#include "AIScene/AIComponents/PickupAffordance.hpp"

PlayerScript::PlayerScript(GameObject* parent)
	:
	Component(parent),
	gameObject(parent),
	transform(gameObject->AddComponent<Transform>()),
	camera(gameObject->AddComponent<Camera>()),
	input(gameObject->AddComponent<Input>()),
	sphereCollider(gameObject->AddComponent<SphereCollider>()),
	rayCaster(gameObject->AddComponent<RayCaster>()),
	affordanceSystem(gameObject->AddComponent<AffordanceSystem>()),
	m_emotionSystem(gameObject->AddComponent<EmotionSystem>())
{
	
}


void PlayerScript::Awake()
{
	movementSpeed = 0.05f;
	lookSensitivity = 0.05f;
	sprintMultiplyer = 4;
	std::function<glm::vec3()> getPlayerPosition = [&]() { return transform->GetPosition(); };
	std::function<glm::vec3()> getPlayerDirection = [&]() { return camera->m_frontDirection; };
	affordanceSystem->AddAffordance<PickupAffordance>()->EnableAbility(getPlayerPosition, getPlayerDirection);
	rayCaster->SetOwnColliderID(sphereCollider->GetColliderID());
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

	std::shared_ptr<GameObject> otherObject;
	int objectID = rayCaster->CastRay(camera->GetPosition(), camera->m_frontDirection, 10);
	if(objectID != -1 && GetAISceneObject != nullptr)
	{
		otherObject = GetAISceneObject(objectID);
		if(otherObject->GetComponent<AffordanceSystem>() != nullptr)
		{
			if(otherObject->GetComponent<AffordanceSystem>()->GetAffordance<PickupAffordance>() != nullptr)
			{
				CheckPickup(otherObject);
			}
		}

		if (otherObject->GetComponent<EmotionSystem>() != nullptr)
		{
			TestEmotions(otherObject);
		}
	}
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

	//// TEST EMOTION SYSTEM ////

	if (input->GetKeyState(YOKAI_INPUT::P))
	{
		// good
		m_emotionSystem->TriggerEmotionalResponse(1, 0.9);
	}

	if (input->GetKeyState(YOKAI_INPUT::L))
	{
		// Meh
		m_emotionSystem->TriggerEmotionalResponse(-0.5, 0.3);
	}

	if (input->GetKeyState(YOKAI_INPUT::M))
	{
		// Scary
		m_emotionSystem->TriggerEmotionalResponse(-1, 1);
	}
		

	////	  END TEST		////

}

void PlayerScript::CheckPickup(std::shared_ptr<GameObject> otherObject)
{
	std::shared_ptr<PickupAffordance> pickupAffordance = affordanceSystem->GetAffordance<PickupAffordance>();
	std::shared_ptr<PickupAffordance> otherPickupAffordance = otherObject->GetComponent<AffordanceSystem>()->GetAffordance<PickupAffordance>();

	if(otherPickupAffordance != nullptr)
	{
		if (pickupAffordance->HasAbility && !pickupAffordance->IsUsing && otherPickupAffordance->HasAffordance && !otherPickupAffordance->IsAffording)
		{
			if(glm::distance(transform->GetPosition(), otherObject->GetComponent<Transform>()->GetPosition()) < 5)
			{
				if (input->GetKeyToggle(YOKAI_INPUT::E))
				{
					pickupAffordance->Interact(otherPickupAffordance);
				}
			}
		}
		else if(pickupAffordance->IsUsing)
		{
			if (input->GetKeyToggle(YOKAI_INPUT::E))
			{
				pickupAffordance->Stop();
			}
		}
	}

}

void PlayerScript::TestEmotions(std::shared_ptr<GameObject> otherObject)
{
	std::shared_ptr<EmotionSystem> otherEmotionSystem = otherObject->GetComponent<EmotionSystem>();

	if (glm::distance(transform->GetPosition(), otherObject->GetComponent<Transform>()->GetPosition()) < 5)
	{
		if (input->GetKeyToggle(YOKAI_INPUT::P))
		{
			// good
			otherEmotionSystem->TriggerEmotionalResponse(1, 0.9);
		}

		if (input->GetKeyToggle(YOKAI_INPUT::L))
		{
			// Meh
			otherEmotionSystem->TriggerEmotionalResponse(-0.5, 0.3);
		}

		if (input->GetKeyToggle(YOKAI_INPUT::M))
		{
			// Scary
			otherEmotionSystem->TriggerEmotionalResponse(-1, 1);
		}
	}
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