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
	m_affordanceSystem->AddAffordance<PickupAffordance>()->EnableAffordance(m_transform);
}

void CubeScript::Start()
{

}

void CubeScript::Update(float deltaTime)
{
	m_boxCollider->SetPosition(m_transform->getPosition());
	m_boxCollider->SetOrientation(m_transform->getRotation());
}

void CubeScript::Draw()
{

}