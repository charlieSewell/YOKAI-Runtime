#include "AIScene.hpp"
#include "Common/PlayerScript.hpp"
#include "NPCScript.hpp"
#include "Components/SphereCollider.hpp"
#include "Components/BoxCollider.hpp"

AIScene::AIScene()
{

}

void AIScene::Init()
{
	Player = objectManager.CreateObject();
	objectManager.GetObject(Player)->AddComponent<PlayerScript>();
	objectManager.GetObject(Player)->Start();

	for(int i=0; i<10; ++i)
	{
		Zombies = objectManager.CreateObject();
		objectManager.GetObject(Zombies)->AddComponent<NPCScript>();
		objectManager.GetObject(Zombies)->Start();
	}

	// COLLIDERS
	InitColliders();
	UIInputObject = objectManager.CreateObject();
	UIinput = objectManager.GetObject(UIInputObject)->AddComponent<Input>();
}

void AIScene::Update(float frameRate)
{
    objectManager.Update(frameRate);
	m_physicsOn = UIinput->GetKeyState('f');
	PhysicsSystem::getInstance().IsDebugEnabled(m_physicsOn);
}

void AIScene::Draw()
{
	objectManager.Draw();
}

void AIScene::Enable()
{
    isEnabled = true;
}

void AIScene::Disable()
{
    isEnabled = false;
}

void AIScene::InitColliders()
{
	Colliders = objectManager.CreateObject();
	// Floor
	objectManager.GetObject(Colliders)->AddComponent<BoxCollider>()->SetExtents(glm::vec3(20, 0.4, 20));
	objectManager.GetObject(Colliders)->AddComponent<Transform>()->setPosition(glm::vec3(15, 0, -15));
	objectManager.GetObject(Colliders)->Start();

	// Left Wall
	objectManager.GetObject(Colliders)->AddComponent<BoxCollider>()->SetExtents(glm::vec3(0.10, 5.0, 5.0));
	objectManager.GetObject(Colliders)->AddComponent<Transform>()->setPosition(glm::vec3(7.0, 0.25, -6.5));
	objectManager.GetObject(Colliders)->Start();
	objectManager.GetObject(Colliders)->GetComponent<BoxCollider>()->SetOrientation(glm::quat(0.966, 0, 0.259, 0));

	// Right Wall
	objectManager.GetObject(Colliders)->AddComponent<BoxCollider>()->SetExtents(glm::vec3(0.10, 5.0, 5.0));
	objectManager.GetObject(Colliders)->AddComponent<Transform>()->setPosition(glm::vec3(18.5, 0.25, -6.5));
	objectManager.GetObject(Colliders)->Start();
	objectManager.GetObject(Colliders)->GetComponent<BoxCollider>()->SetOrientation(glm::quat(0.966, 0, -0.259, 0));

	// Back Wall
	objectManager.GetObject(Colliders)->AddComponent<BoxCollider>()->SetExtents(glm::vec3(5.0, 5.0, 0.10));
	objectManager.GetObject(Colliders)->AddComponent<Transform>()->setPosition(glm::vec3(12, 0.25, -1.775));
	objectManager.GetObject(Colliders)->Start();
}