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
	offset.SetPosition(-0.2f, -1.65f, 0.0f);
	m_gameObject->AddComponent<DrawableEntity>()->LoadModel("content/aiScene/models/dog/husky.gltf");
	m_gameObject->GetComponent<DrawableEntity>()->SetOffset(offset.GetMatrix());
	m_transform->SetScale(0.35);
	//m_sphereCollider->SetRadius(1.0);
	m_boxCollider->SetExtents(0.7, 0.45, 0.3);
	m_boxCollider->Start();
	m_boxCollider->StaticSet();

	m_rayCaster->SetOwnColliderID(m_boxCollider->GetColliderID());
	m_automatedBehaviours->SetCastHeight(0.5f);

	m_emotionSystem->SetTraits(1.2, 1.6);

	std::function<glm::vec3()> getPosition = [&]() { return m_transform->GetPosition(); };
	std::function<glm::vec3()> getHeading = [&]() { return m_automatedBehaviours->Heading; };
	m_affordanceSystem->AddAffordance<PickupAffordance>()->EnableAbility(getPosition, getHeading);
	m_affordanceSystem->GetAffordance<PickupAffordance>()->PickupHeightOffset = 0.25;
	m_affordanceSystem->GetAffordance<PickupAffordance>()->PickupFrontOffset = 1;
	m_affordanceSystem->GetAffordance<PickupAffordance>()->EnableAffordance(m_transform, m_boxCollider);
	m_affordanceSystem->AddAffordance<BiteAffordance>()->EnableAbility(m_emotionSystem);
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
			if(otherObject->GetComponent<AffordanceSystem>()->GetAffordance<BiteAffordance>() != nullptr && m_emotionSystem->GetCurrentEmotion() == EMOTION::FRUSTRATED)
			{
				iDunnoHesDoingAnAffordanceVariableNamesAreHardOkay = CheckBite(otherObject);
			}
			else if (otherObject->GetComponent<AffordanceSystem>()->GetAffordance<PickupAffordance>() != nullptr)
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
		m_emotionSystem->TriggerEmotionalResponse(-1, 0.00025);
		m_automatedBehaviours->Acceleration = 0.0f;
		iDunnoHesDoingAnAffordanceVariableNamesAreHardOkay = true;
		m_isPickedUp = true;
	}
	else if (!iDunnoHesDoingAnAffordanceVariableNamesAreHardOkay)
	{
		if(m_isPickedUp)
		{
			glm::vec3 temp = m_transform->GetPosition();
			temp.y = 0.5;
			m_transform->SetPosition(temp);
			m_automatedBehaviours->Angle = 0;
			m_automatedBehaviours->Heading = glm::vec3(0.5f, 0.0f, 0.5f);
			m_automatedBehaviours->Acceleration = m_topSpeed;
			m_transform->SetRotation(glm::quat{});
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
		m_evadeActive = false;
		m_automatedBehaviours->wander();
		m_automatedBehaviours->TopSpeed = m_topSpeed;
		break;
	case EMOTION::FEAR:
		if (!m_evadeActive)
		{
			m_evadePosition = m_transform->GetPosition();
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
			m_automatedBehaviours->seek(otherObject->GetComponent<Transform>()->GetPosition());

			if (glm::distance(m_transform->GetPosition(), otherObject->GetComponent<Transform>()->GetPosition()) < 2)
			{
				pickupAffordance->Interact(otherPickupAffordance);
				//pickupAffordance->HasAffordance = false; // stops getting picked up while picking things up

				int otherColliderID = 0;
				if (otherObject->GetComponent<BoxCollider>() != nullptr)
				{
					m_rayCaster->SetExcludedColliderID(otherObject->GetComponent<BoxCollider>()->GetColliderID());
				}
				else if (otherObject->GetComponent<SphereCollider>() != nullptr)
				{
					m_rayCaster->SetExcludedColliderID(otherObject->GetComponent<SphereCollider>()->GetColliderID());
				}
			}

			m_automatedBehaviours->accelerate();

			return true;
		}
	}

	return false;
}

bool DogScript::CheckBite(std::shared_ptr<GameObject> otherObject)
{
	std::shared_ptr<BiteAffordance> biteAffordance = m_affordanceSystem->GetAffordance<BiteAffordance>();
	std::shared_ptr<BiteAffordance> otherBiteAffordance = otherObject->GetComponent<AffordanceSystem>()->GetAffordance<BiteAffordance>();

	if (otherBiteAffordance != nullptr)
	{
		if (biteAffordance->HasAbility && otherBiteAffordance->HasAffordance)
		{
			// Object we want is directly in front so set this to avoid front collision detection
			m_automatedBehaviours->frontFeelerHit = -1;
			m_automatedBehaviours->feelerLeftHit = -1;
			m_automatedBehaviours->feelerRightHit = -1;
			m_automatedBehaviours->seek(otherObject->GetComponent<Transform>()->GetPosition());

			if (glm::distance(m_transform->GetPosition(), otherObject->GetComponent<Transform>()->GetPosition()) < 2)
			{
				biteAffordance->Interact(otherBiteAffordance);

				int otherColliderID = 0;
				if (otherObject->GetComponent<BoxCollider>() != nullptr)
				{
					m_rayCaster->SetExcludedColliderID(otherObject->GetComponent<BoxCollider>()->GetColliderID());
				}
				else if (otherObject->GetComponent<SphereCollider>() != nullptr)
				{
					m_rayCaster->SetExcludedColliderID(otherObject->GetComponent<SphereCollider>()->GetColliderID());
				}
			}

			m_gameObject->GetComponent<DrawableEntity>()->SetAnimation("Attack");
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