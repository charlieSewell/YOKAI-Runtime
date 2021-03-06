#include "BlakeScript.hpp"
#include "Components/BoxCollider.hpp"

BlakeScript::BlakeScript(GameObject* parent)
	:
	Component(parent),
	m_gameObject(parent),
	m_transform(m_gameObject->AddComponent<Transform>()),
	m_boxCollider(m_gameObject->AddComponent<BoxCollider>()),
	m_rayCaster(m_gameObject->AddComponent<RayCaster>()),
	m_automatedBehaviours(m_gameObject->AddComponent<AutomatedBehaviours>()),
	m_emotionSystem(m_gameObject->AddComponent<EmotionSystem>()),
	m_affordanceSystem(m_gameObject->AddComponent<AffordanceSystem>())
{
	Awake();
}


void BlakeScript::Awake()
{
	Transform offset;
	offset.SetPosition(0.0f, -1.0f, 0.0f);
	m_gameObject->AddComponent<DrawableEntity>()->LoadModel("content/aiScene/models/blake/blake.gltf");
	m_gameObject->AddComponent<DrawableEntity>()->SetOffset(offset.GetMatrix());
	m_transform->SetScale(1.1);
	m_boxCollider->SetExtents(0.35, 1.1, 0.35);
	m_boxCollider->Start();
	m_rayCaster->SetOwnColliderID(m_boxCollider->GetColliderID());
	m_automatedBehaviours->TopSpeed = m_topSpeed;
	m_automatedBehaviours->SetCastHeight(0.5f);
	m_boxCollider->StaticSet();

	std::function<glm::vec3()> getPosition = [&]() { return m_transform->GetPosition(); };
	std::function<glm::vec3()> getHeading = [&]() { return m_automatedBehaviours->Heading; };
	m_affordanceSystem->AddAffordance<PickupAffordance>()->EnableAbility(getPosition, getHeading);
	m_affordanceSystem->GetAffordance<PickupAffordance>()->PickupFrontOffset = 0.5;
	m_affordanceSystem->GetAffordance<PickupAffordance>()->PickupHeightOffset = 0.25;
	m_affordanceSystem->AddAffordance<BiteAffordance>()->EnableAffordance(getPosition, m_emotionSystem);
}

void BlakeScript::Start()
{
	m_automatedBehaviours->RotationSpeed = 0.05;
}

void BlakeScript::Update(float deltaTime)
{
	bool iDunnoHesDoingAnAffordanceVariableNamesAreHardOkay = false;

	std::shared_ptr<GameObject> otherObject;
	int objectID = m_automatedBehaviours->frontFeelerHit;
	if (objectID != -1 && m_emotionSystem->GetCurrentEmotion() != EMOTION::FEAR)
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
	else if (m_affordanceSystem->GetAffordance<PickupAffordance>()->IsUsing)
	{
		DropPickup(deltaTime);
	}

	if (!iDunnoHesDoingAnAffordanceVariableNamesAreHardOkay)
	{
		StateMachine();
	}

	SetAnimation();
}

void BlakeScript::SetAnimation()
{
	if (m_automatedBehaviours->Acceleration < m_topSpeed * 0.10)	// stand still if moving at 10% speed
	{
		m_gameObject->GetComponent<DrawableEntity>()->SetAnimation("idle");
	}
	else if (m_automatedBehaviours->Acceleration > m_topSpeed * 1.10)		// run if moving at 110% speed
	{
		m_gameObject->GetComponent<DrawableEntity>()->SetAnimation("run");
	}
	else
	{
		m_gameObject->GetComponent<DrawableEntity>()->SetAnimation("walk");
	}
}

void BlakeScript::Draw()
{

}

void BlakeScript::StateMachine()
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
			m_evadePosition = m_transform->GetPosition();
			m_evadeActive = true;
		}
		m_automatedBehaviours->evade(m_evadePosition);
		m_automatedBehaviours->TopSpeed = m_topSpeed;
		break;
	case EMOTION::FEAR:
		if(!m_evadeActive)
		{
			m_evadePosition = m_transform->GetPosition();
			m_evadeActive = true;
		}
		m_automatedBehaviours->evade(m_evadePosition);
		m_automatedBehaviours->TopSpeed = m_topSpeed * 4 ;
		break;
	}

	m_automatedBehaviours->accelerate();
}


bool BlakeScript::CheckPickup(std::shared_ptr<GameObject> otherObject)
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

void BlakeScript::DropPickup(float deltaTime)
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
		m_isTimerSet = false;
	}
}