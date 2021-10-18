#include "NPCScript.hpp"

NPCScript::NPCScript(GameObject* parent)
	:
	Component(parent),
	gameObject(parent),
	transform(gameObject->AddComponent<Transform>()),
	sphereCollider(gameObject->AddComponent<SphereCollider>()),
	rayCaster(gameObject->AddComponent<RayCaster>()),
	automatedBehaviours(gameObject->AddComponent<AutomatedBehaviours>())
{
	Awake();
}


void NPCScript::Awake()
{
	gameObject->AddComponent<DrawableEntity>()->LoadModel("content/aiScene/models/Zombie/ZombieSmooth.gltf");
	transform->setScale(0.15);
	transform->setPosition(glm::vec3(16, 0.5, -5));
	sphereCollider->SetRadius(0.5);
}

void NPCScript::Start()
{
	automatedBehaviours->RotationSpeed = 0.05;
}

void NPCScript::Update(float deltaTime)
{
	automatedBehaviours->wander();
	automatedBehaviours->accelerate(0.015);
	sphereCollider->SetPosition(glm::vec3(transform->getPosition().x, transform->getPosition().y +0.5, transform->getPosition().z));
}

void NPCScript::Draw()
{

}