#include "CubeScript.hpp"

CubeScript::CubeScript(GameObject* parent)
	:
	Component(parent),
	m_gameObject(parent),
	m_transform(m_gameObject->AddComponent<Transform>()),
	m_boxCollider(m_gameObject->AddComponent<BoxCollider>()),
	m_affordanceSystem(m_gameObject->AddComponent<AffordanceSystem>())
{
	Awake();
}


void CubeScript::Awake()
{
	Transform offset;
	offset.setPosition(0.0f, -1.65f, 0.0f);
	m_gameObject->AddComponent<DrawableEntity>()->LoadModel("content/aiScene/models/shay/shay.gltf");
	m_gameObject->GetComponent<DrawableEntity>()->SetOffset(offset.getMatrix());
	m_transform->setScale(0.25);
	m_boxCollider->SetExtents(glm::vec3(0.25, 0.25, 0.25));
	m_boxCollider->Start();
	//m_boxCollider->StaticSet();
	m_affordanceSystem->AddAffordance<PickupAffordance>()->EnableAffordance(m_transform);
}

void CubeScript::Start()
{
	m_boxCollider->SetLinearVelocity(glm::dvec3(0, 0, 0));
	m_boxCollider->SetAngularVelocity(glm::dvec3(0, 0, 0));
	m_boxCollider->SetMass(2.0);
	//m_boxCollider->SetIsStaticObject(false);
	m_boxCollider->SetInertiaTensor();
	//m_boxCollider->SetOrientation(glm::quat(1.0, 0, 0, 0));
	m_boxCollider->SetCollisionCategory(Physics::CATEGORY2);
	m_boxCollider->SetCollisionMaskBits(Physics::CATEGORY1 | Physics::CATEGORY2);
	//m_objectManager.GetObject(Plank2)->GetComponent<BoxCollider>()->SetOrientation(glm::quat(0.854, 0.354, -0.146, 0.354));
	m_boxCollider->SetGravityAffected(true);
	//m_boxCollider->StaticSet();
	m_boxCollider->SetIsStaticObject(false);
	//m_boxCollider->SetGravityAffected(true);
}

void CubeScript::Update(float deltaTime)
{
	//m_boxCollider->SetPosition(m_transform->getPosition());
	//m_boxCollider->SetOrientation(m_transform->getRotation());
}

void CubeScript::Draw()
{

}