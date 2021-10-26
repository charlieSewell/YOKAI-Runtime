#include "ZombieScript.hpp"
#include "Components/BoxCollider.hpp"

ZombieScript::ZombieScript(GameObject* parent)
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


void ZombieScript::Awake()
{
	m_gameObject->AddComponent<DrawableEntity>()->LoadModel("content/aiScene/models/Zombie/ZombieSmooth.gltf");
	m_transform->setScale(0.25);
	m_sphereCollider->SetRadius(1.0);
	m_rayCaster->setOwnColliderID(m_sphereCollider->GetColliderID());
	m_automatedBehaviours->TopSpeed = 0.010;
	m_automatedBehaviours->SetCastHeight(0.5f);

	//std::function<void(glm::vec3)> setPosition = [&](glm::vec3 newPosition) { transform->setPosition(newPosition); };
	//affordanceSystem->AddAffordance<PickupAffordance>()->EnableAffordance(setPosition);

	std::function<glm::vec3()> getPosition = [&]() { return m_transform->getPosition(); };
	std::function<glm::vec3()> getHeading = [&]() { return m_automatedBehaviours->Heading; };
	m_affordanceSystem->AddAffordance<PickupAffordance>()->EnableAbility(getPosition, getHeading);
	m_affordanceSystem->GetAffordance<PickupAffordance>()->PickupFrontOffset = 1;
}

void ZombieScript::Start()
{
	m_automatedBehaviours->RotationSpeed = 0.05;
}

void ZombieScript::Update(float deltaTime)
{
	int fakeState = 0;

	if(m_automatedBehaviours->Acceleration < m_automatedBehaviours->TopSpeed * 0.10)	// stand still if moving at 10% speed
	{
		m_gameObject->GetComponent<DrawableEntity>()->SetAnimation("ZombieIdle");
	}
	else
	{
		m_gameObject->GetComponent<DrawableEntity>()->SetAnimation("ZombieWalk");
	}

	std::shared_ptr<GameObject> otherObject;
	int objectID = m_automatedBehaviours->frontFeelerHit;
	if (objectID != -1)
	{
		otherObject = GetAISceneObject(objectID);
		if (otherObject->GetComponent<AffordanceSystem>() != nullptr)
		{
			if (otherObject->GetComponent<AffordanceSystem>()->GetAffordance<PickupAffordance>() != nullptr)
			{
				fakeState = CheckPickup(otherObject);
			}
		}
	}

	if(!fakeState)
	{
		m_automatedBehaviours->wander();
	}

	m_automatedBehaviours->accelerate();
	m_sphereCollider->SetPosition(glm::vec3(m_transform->getPosition().x, m_transform->getPosition().y + 1, m_transform->getPosition().z));
}

void ZombieScript::Draw()
{

}

bool ZombieScript::CheckPickup(std::shared_ptr<GameObject> otherObject)
{
	std::shared_ptr<PickupAffordance> pickupAffordance = m_affordanceSystem->GetAffordance<PickupAffordance>();
	std::shared_ptr<PickupAffordance> otherPickupAffordance = otherObject->GetComponent<AffordanceSystem>()->GetAffordance<PickupAffordance>();

	if (otherPickupAffordance != nullptr)
	{
		if (pickupAffordance->HasAbility && otherPickupAffordance->IsAvailable && !pickupAffordance->IsActive)
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
				if(otherObject->GetComponent<BoxCollider>() != nullptr)
				{
					m_rayCaster->setExcludedColliderID(otherObject->GetComponent<BoxCollider>()->GetColliderID());
				}
				else if(otherObject->GetComponent<SphereCollider>() != nullptr)
				{
					m_rayCaster->setExcludedColliderID(otherObject->GetComponent<SphereCollider>()->GetColliderID());
				}
			}

			return true;
		}
		else if (pickupAffordance->IsActive)
		{
			// logic to drop box
			//pickupAffordance->Stop();
			//rayCaster->setExcludedColliderID(-1);
		}
	}

	return false;
}