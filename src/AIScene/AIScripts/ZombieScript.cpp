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
	offset.setPosition(0.0f, -4.0f, 0.0f);
	m_gameObject->AddComponent<DrawableEntity>()->LoadModel("content/aiScene/models/Zombie/ZombieSmooth.gltf");
	m_gameObject->AddComponent<DrawableEntity>()->SetOffset(offset.getMatrix());
	m_transform->setScale(0.25);
	m_boxCollider->SetExtents(0.4, 1.1, 0.4);
	m_boxCollider->Start();
	m_boxCollider->StaticSet();
	m_rayCaster->setOwnColliderID(m_boxCollider->GetColliderID());
	m_automatedBehaviours->TopSpeed = m_topSpeed;
	m_automatedBehaviours->SetCastHeight(0.5f);
	m_automatedBehaviours->RotationSpeed = 0.005;
}

void ZombieScript::Start()
{
	
}

void ZombieScript::Update(float deltaTime)
{
	int fakeState = 0;

	if(m_automatedBehaviours->Acceleration < m_topSpeed * 0.10)	// stand still if moving at 10% speed
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
			/*if (otherObject->GetComponent<AffordanceSystem>()->GetAffordance<PickupAffordance>() != nullptr)
			{
				fakeState = CheckPickup(otherObject);
			}*/
		}
	}

	if(!fakeState)
	{
		m_automatedBehaviours->wander();
	}

	m_automatedBehaviours->accelerate();
}

void ZombieScript::Draw()
{

}