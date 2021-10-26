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
	m_gameObject->AddComponent<DrawableEntity>()->LoadModel("content/aiScene/models/shay/shay.gltf");
	m_transform->setScale(0.25);
	m_boxCollider->SetExtents(glm::vec3(0.5, 0.5, 0.5));

	//std::function<void(Transform)> setTransform = [&](Transform newTransform) { *transform = newTransform; };
	m_affordanceSystem->AddAffordance<PickupAffordance>()->EnableAffordance(m_transform);
}

void CubeScript::Start()
{

}

void CubeScript::Update(float deltaTime)
{
	m_boxCollider->SetPosition(glm::vec3(m_transform->getPosition().x, m_transform->getPosition().y + 0.5, m_transform->getPosition().z));
}

void CubeScript::Draw()
{

}