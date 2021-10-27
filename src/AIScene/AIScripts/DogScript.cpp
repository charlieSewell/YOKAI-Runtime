#include "DogScript.hpp"
#include "Components/BoxCollider.hpp"

DogScript::DogScript(GameObject* parent)
	:
	Component(parent),
	m_gameObject(parent),
	m_transform(m_gameObject->AddComponent<Transform>()),
	m_sphereCollider(m_gameObject->AddComponent<SphereCollider>()),
	m_rayCaster(m_gameObject->AddComponent<RayCaster>()),
	m_automatedBehaviours(m_gameObject->AddComponent<AutomatedBehaviours>()),
	m_emotionSystem(m_gameObject->AddComponent<EmotionSystem>()),
	m_affordanceSystem(m_gameObject->AddComponent<AffordanceSystem>())
{
	Awake();
}


void DogScript::Awake()
{
	m_gameObject->AddComponent<DrawableEntity>()->LoadModel("content/aiScene/models/dog/husky.gltf");
	m_transform->setScale(0.35);
	m_sphereCollider->SetRadius(1.0);
	m_rayCaster->setOwnColliderID(m_sphereCollider->GetColliderID());
	m_automatedBehaviours->SetCastHeight(0.5f);

	//std::function<void(glm::vec3)> setPosition = [&](glm::vec3 newPosition) { transform->setPosition(newPosition); };
	//affordanceSystem->AddAffordance<PickupAffordance>()->EnableAffordance(setPosition);

	std::function<glm::vec3()> getPosition = [&]() { return m_transform->getPosition(); };
	std::function<glm::vec3()> getHeading = [&]() { return m_automatedBehaviours->Heading; };
	m_affordanceSystem->AddAffordance<PickupAffordance>()->EnableAbility(getPosition, getHeading);
	m_affordanceSystem->GetAffordance<PickupAffordance>()->PickupHeightOffset = 0.5;
	m_affordanceSystem->GetAffordance<PickupAffordance>()->PickupFrontOffset = 1;

	m_affordanceSystem->AddAffordance<PickupAffordance>()->EnableAffordance(m_transform);
}

void DogScript::Start()
{
	m_automatedBehaviours->RotationSpeed = 0.05;
}

void DogScript::Update(float deltaTime)
{
	{
		bool iDunnoHesDoingAnAffordanceVariableNamesAreHardOkay = false;

		std::shared_ptr<GameObject> otherObject;
		int objectID = m_automatedBehaviours->frontFeelerHit;
		if (objectID != -1)
		{
			otherObject = GetAISceneObject(objectID);
			if (otherObject->GetComponent<AffordanceSystem>() != nullptr)
			{
				if (otherObject->GetComponent<AffordanceSystem>()->GetAffordance<PickupAffordance>() != nullptr)
				{
					iDunnoHesDoingAnAffordanceVariableNamesAreHardOkay = CheckPickup(otherObject);
				}
			}
		}

		//if dog is picked turn into limp boi
		if(m_affordanceSystem->GetAffordance<PickupAffordance>()->IsAffording)
		{
			m_automatedBehaviours->Acceleration = 0;
			m_automatedBehaviours->Angle = 0;
			iDunnoHesDoingAnAffordanceVariableNamesAreHardOkay = true;
		}

		if (!iDunnoHesDoingAnAffordanceVariableNamesAreHardOkay)
		{
			StateMachine();
		}

		SetAnimation();

		m_sphereCollider->SetPosition(glm::vec3(m_transform->getPosition().x, m_transform->getPosition().y + 1, m_transform->getPosition().z));
	}
}

void DogScript::SetAnimation()
{
	if (m_automatedBehaviours->Acceleration < m_topSpeed * 0.10)	// stand still if moving at 10% speed
	{
		m_gameObject->GetComponent<DrawableEntity>()->SetAnimation("Idle");
	}
	else if (m_automatedBehaviours->Acceleration > m_topSpeed * 1.01)
	{
		m_gameObject->GetComponent<DrawableEntity>()->SetAnimation("Gallop");
	}
	else
	{
		m_gameObject->GetComponent<DrawableEntity>()->SetAnimation("Walk");
	}
}

void DogScript::Draw()
{

}

void DogScript::StateMachine()
{
	switch (m_emotionSystem->GetCurrentEmotion())
	{
	case EMOTION::CALM:
		m_evadeActive = false;
		m_automatedBehaviours->wander();
		m_automatedBehaviours->TopSpeed = m_topSpeed;
		break;
	case EMOTION::EXCITED:
		m_evadeActive = false;
		m_automatedBehaviours->wander();
		m_automatedBehaviours->TopSpeed = m_topSpeed * 1.5;
		break;
	case EMOTION::BORED:
		m_evadeActive = false;
		m_automatedBehaviours->wander();
		m_automatedBehaviours->TopSpeed = m_topSpeed * 0.5;
		break;
	case EMOTION::FRUSTRATED:
		if (!m_evadeActive)
		{
			m_evadePosition = m_transform->getPosition();
			m_evadeActive = true;
		}
		m_automatedBehaviours->evade(m_evadePosition);
		m_automatedBehaviours->TopSpeed = m_topSpeed;
		break;
	case EMOTION::FEAR:
		if (!m_evadeActive)
		{
			m_evadePosition = m_transform->getPosition();
			m_evadeActive = true;
		}
		m_automatedBehaviours->evade(m_evadePosition);
		m_automatedBehaviours->TopSpeed = m_topSpeed * 4;
		break;
	}

	m_automatedBehaviours->accelerate();
}

bool DogScript::CheckPickup(std::shared_ptr<GameObject> otherObject)
{
	std::shared_ptr<PickupAffordance> pickupAffordance = m_affordanceSystem->GetAffordance<PickupAffordance>();
	std::shared_ptr<PickupAffordance> otherPickupAffordance = otherObject->GetComponent<AffordanceSystem>()->GetAffordance<PickupAffordance>();

	if (otherPickupAffordance != nullptr)
	{
		if (pickupAffordance->HasAbility && !pickupAffordance->IsUsing && otherPickupAffordance->HasAffordance && !otherPickupAffordance->IsAffording)
		{
			// Object we want is directly in front so set this to avoid front collision detection
			m_automatedBehaviours->frontFeelerHit = -1;
			m_automatedBehaviours->feelerLeftHit = -1;
			m_automatedBehaviours->feelerRightHit = -1;
			m_automatedBehaviours->seek(otherObject->GetComponent<Transform>()->getPosition());

			if (glm::distance(m_transform->getPosition(), otherObject->GetComponent<Transform>()->getPosition()) < 2)
			{
				pickupAffordance->Interact(otherPickupAffordance);

				int otherColliderID = 0;
				if (otherObject->GetComponent<BoxCollider>() != nullptr)
				{
					m_rayCaster->setExcludedColliderID(otherObject->GetComponent<BoxCollider>()->GetColliderID());
				}
				else if (otherObject->GetComponent<SphereCollider>() != nullptr)
				{
					m_rayCaster->setExcludedColliderID(otherObject->GetComponent<SphereCollider>()->GetColliderID());
				}
			}

			m_automatedBehaviours->accelerate();

			return true;
		}
		else if (pickupAffordance->IsUsing)
		{
			// logic to drop box
			//pickupAffordance->Stop();
			//rayCaster->setExcludedColliderID(-1);
		}
	}

	return false;
}