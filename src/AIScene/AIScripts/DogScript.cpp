#include "DogScript.hpp"
#include "Components/BoxCollider.hpp"

DogScript::DogScript(GameObject* parent)
	:
	Component(parent),
	m_gameObject(parent),
	m_transform(m_gameObject->AddComponent<Transform>()),
	m_rayCaster(m_gameObject->AddComponent<RayCaster>()),
	m_automatedBehaviours(m_gameObject->AddComponent<AutomatedBehaviours>()),
	m_emotionSystem(m_gameObject->AddComponent<EmotionSystem>()),
	m_affordanceSystem(m_gameObject->AddComponent<AffordanceSystem>()),
	m_boxCollider(m_gameObject->AddComponent<BoxCollider>())
{
	Awake();
}


void DogScript::Awake()
{
	Transform offset;
	offset.setPosition(-0.2f, -1.65f, 0.0f);
	m_gameObject->AddComponent<DrawableEntity>()->LoadModel("content/aiScene/models/dog/husky.gltf");
	m_gameObject->GetComponent<DrawableEntity>()->SetOffset(offset.getMatrix());
	m_transform->setScale(0.35);
	//m_sphereCollider->SetRadius(1.0);
	m_boxCollider->SetExtents(0.7, 0.45, 0.3);
	m_boxCollider->Start();

	m_rayCaster->setOwnColliderID(m_boxCollider->GetColliderID());
	m_automatedBehaviours->SetCastHeight(0.5f);

	std::function<glm::vec3()> getPosition = [&]() { return m_transform->getPosition(); };
	std::function<glm::vec3()> getHeading = [&]() { return m_automatedBehaviours->Heading; };
	m_affordanceSystem->AddAffordance<PickupAffordance>()->EnableAbility(getPosition, getHeading);
	m_affordanceSystem->GetAffordance<PickupAffordance>()->PickupHeightOffset = 0.25;
	m_affordanceSystem->GetAffordance<PickupAffordance>()->PickupFrontOffset = 1;
	m_affordanceSystem->GetAffordance<PickupAffordance>()->EnableAffordance(m_transform, m_boxCollider);
}

void DogScript::Start()
{
	m_automatedBehaviours->RotationSpeed = 0.025;
}

void DogScript::Update(float deltaTime)
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
	else if(m_affordanceSystem->GetAffordance<PickupAffordance>()->IsUsing)
	{
		DropPickup(deltaTime);
	}

	//if dog is picked up turn into limp boi
	if(m_affordanceSystem->GetAffordance<PickupAffordance>()->IsAffording)
	{
		m_automatedBehaviours->Acceleration = 0;
		m_automatedBehaviours->Angle = 0;
		iDunnoHesDoingAnAffordanceVariableNamesAreHardOkay = true;
		m_isPickedUp = true;
	}
	else if (!iDunnoHesDoingAnAffordanceVariableNamesAreHardOkay)
	{
		if(m_isPickedUp)
		{
			glm::vec3 temp = m_transform->getPosition();
			temp.y = 0.5;
			m_transform->setPosition(temp);
			m_automatedBehaviours->Angle = 0;
			m_automatedBehaviours->Heading = glm::vec3{};
			m_transform->setRotation(glm::quat{});
			m_isPickedUp = false;
		}
		
		StateMachine();
	}

	SetAnimation();
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
				//pickupAffordance->HasAffordance = false; // stops getting picked up while picking things up

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
	}

	return false;
}

void DogScript::DropPickup(float deltaTime)
{
	if (!m_isTimerSet)
	{
		m_timer = 0.0f;
		m_isTimerSet = true;
	}
	m_timer += deltaTime;

	if (m_timer > 10)
	{
		m_affordanceSystem->GetAffordance<PickupAffordance>()->Stop();
		m_affordanceSystem->GetAffordance<PickupAffordance>()->HasAffordance = true;
		m_isTimerSet = false;
	}
}