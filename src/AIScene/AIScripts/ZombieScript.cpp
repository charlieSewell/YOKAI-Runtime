#include "ZombieScript.hpp"
#include "Components/BoxCollider.hpp"

ZombieScript::ZombieScript(GameObject* parent)
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


void ZombieScript::Awake()
{
	Transform offset;
	offset.SetPosition(0.0f, -4.0f, 0.0f);
	m_gameObject->AddComponent<DrawableEntity>()->LoadModel("content/aiScene/models/Zombie/ZombieSmooth.gltf");
	m_gameObject->AddComponent<DrawableEntity>()->SetOffset(offset.GetMatrix());
	m_transform->SetScale(0.25);
	m_boxCollider->SetExtents(0.4, 1.1, 0.4);
	m_boxCollider->Start();
	m_boxCollider->StaticSet();
	m_rayCaster->SetOwnColliderID(m_boxCollider->GetColliderID());
	m_automatedBehaviours->TopSpeed = m_topSpeed;
	m_automatedBehaviours->SetCastHeight(0.5f);
	m_automatedBehaviours->RotationSpeed = 0.005;

	m_emotionSystem->SetTraits(0.2, 0.8);

	m_affordanceSystem->AddAffordance<BiteAffordance>()->EnableAbility(m_emotionSystem);
}

void ZombieScript::Start()
{

}

void ZombieScript::Update(float deltaTime)
{
	bool iDunnoHesDoingAnAffordanceVariableNamesAreHardOkay = false;

	std::shared_ptr<GameObject> otherObject;
	int objectID = m_automatedBehaviours->frontFeelerHit;
	if (objectID != -1)
	{
		otherObject = GetAISceneObject(objectID);
		if (otherObject->GetComponent<AffordanceSystem>() != nullptr)
		{
			if (otherObject->GetComponent<AffordanceSystem>()->GetAffordance<BiteAffordance>() != nullptr)
			{
				iDunnoHesDoingAnAffordanceVariableNamesAreHardOkay = CheckBite(otherObject);
			}
		}
	}

	if (!iDunnoHesDoingAnAffordanceVariableNamesAreHardOkay)
	{
		StateMachine();
	}

	SetAnimation();
}

void ZombieScript::SetAnimation()
{
	if (m_automatedBehaviours->Acceleration < m_topSpeed * 0.10)	// stand still if moving at 10% speed
	{
		m_gameObject->GetComponent<DrawableEntity>()->SetAnimation("ZombieIdle");
	}
	else if (m_automatedBehaviours->Acceleration > m_topSpeed * 1.01)
	{
		//m_gameObject->GetComponent<DrawableEntity>()->SetAnimation("Gallop");
	}
	else
	{
		m_gameObject->GetComponent<DrawableEntity>()->SetAnimation("ZombieWalk");
	}
}

void ZombieScript::Draw()
{

}

void ZombieScript::StateMachine()
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

bool ZombieScript::CheckBite(std::shared_ptr<GameObject> otherObject)
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
				m_gameObject->GetComponent<DrawableEntity>()->SetAnimation("ZombieAttack");
			}
			else
			{
				biteAffordance->Stop();
			}

			//m_gameObject->GetComponent<DrawableEntity>()->SetAnimation("ZombieAttack");
			m_automatedBehaviours->accelerate();

			return true;
		}
	}

	return false;
}