#include "CubeScript.hpp"

CubeScript::CubeScript(GameObject* parent)
	:
	Component(parent),
	gameObject(parent),
	transform(gameObject->AddComponent<Transform>()),
	boxCollider(gameObject->AddComponent<BoxCollider>()),
	affordanceSystem(gameObject->AddComponent<AffordanceSystem>())
{
	Awake();
}


void CubeScript::Awake()
{
	gameObject->AddComponent<DrawableEntity>()->LoadModel("content/aiScene/models/shay/shay.gltf");
	transform->setScale(0.25);
	boxCollider->SetExtents(glm::vec3(0.5, 0.5, 0.5));

	std::function<void(glm::vec3)> setPosition = [&](glm::vec3 newPosition) { transform->setPosition(newPosition); };
	affordanceSystem->AddAffordance<PickupAffordance>()->EnableAffordance(setPosition);
}

void CubeScript::Start()
{

}

void CubeScript::Update(float deltaTime)
{
	boxCollider->SetPosition(glm::vec3(transform->getPosition().x, transform->getPosition().y + 0.5, transform->getPosition().z));
}

void CubeScript::Draw()
{

}