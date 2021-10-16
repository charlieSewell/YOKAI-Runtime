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

	Cube = objectManager.CreateObject();
	objectManager.GetObject(Cube)->AddComponent<DrawableEntity>()->LoadModel("content/aiScene/models/shay/shay.gltf");
	objectManager.GetObject(Cube)->Start();
	objectManager.GetObject(Cube)->GetComponent<Transform>()->setScale(0.5);
	objectManager.GetObject(Cube)->GetComponent<Transform>()->setPosition(glm::vec3(5, 0, 20));

	Cube = objectManager.CreateObject();
	objectManager.GetObject(Cube)->AddComponent<DrawableEntity>()->LoadModel("content/aiScene/models/house/house.gltf");
	objectManager.GetObject(Cube)->Start();
	objectManager.GetObject(Cube)->GetComponent<Transform>()->setScale(2.0);
	objectManager.GetObject(Cube)->GetComponent<Transform>()->setPosition(glm::vec3(0, 0, 0));

	for(int i=0; i<10; ++i)
	{
		Zombies = objectManager.CreateObject();
		objectManager.GetObject(Zombies)->AddComponent<NPCScript>();
		objectManager.GetObject(Zombies)->GetComponent<Transform>()->setPosition(glm::vec3(-10 + i*3, 0, 30));
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
	PhysicsSystem::getInstance().RendererUpdate();
	m_physicsOn = UIinput->GetKeyState('f');
}

void AIScene::Draw()
{
	objectManager.Draw();
	if(m_physicsOn)
		PhysicsSystem::getInstance().Draw();
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
	objectManager.GetObject(Colliders)->AddComponent<BoxCollider>()->SetExtents(glm::vec3(27.75, 0.4, 20.5));
	objectManager.GetObject(Colliders)->AddComponent<Transform>()->setPosition(glm::vec3(-9.75, 0, 14.0));
	objectManager.GetObject(Colliders)->Start();

	// Back fence
	objectManager.GetObject(Colliders)->AddComponent<BoxCollider>()->SetExtents(glm::vec3(27.75, 5.0, 0.10));
	objectManager.GetObject(Colliders)->AddComponent<Transform>()->setPosition(glm::vec3(-9.75 , 0.25, 34.5));
	objectManager.GetObject(Colliders)->Start();

	// Left fence
	objectManager.GetObject(Colliders)->AddComponent<BoxCollider>()->SetExtents(glm::vec3(20.5, 5.0, 0.10));
	objectManager.GetObject(Colliders)->AddComponent<Transform>()->setPosition(glm::vec3(18.0, 0.25, 14.0));
	objectManager.GetObject(Colliders)->Start();
	objectManager.GetObject(Colliders)->GetComponent<BoxCollider>()->SetOrientation(glm::quat(0.707, 0, 0.707, 0));

	// Right fence
	objectManager.GetObject(Colliders)->AddComponent<BoxCollider>()->SetExtents(glm::vec3(20.5, 5.0, 0.10));
	objectManager.GetObject(Colliders)->AddComponent<Transform>()->setPosition(glm::vec3(-37.25, 0.25, 14.0));
	objectManager.GetObject(Colliders)->Start();
	objectManager.GetObject(Colliders)->GetComponent<BoxCollider>()->SetOrientation(glm::quat(0.707, 0, 0.707, 0));

	// Front of house
	objectManager.GetObject(Colliders)->AddComponent<BoxCollider>()->SetExtents(glm::vec3(27.75, 5.0, 0.10));
	objectManager.GetObject(Colliders)->AddComponent<Transform>()->setPosition(glm::vec3(-9.75, 0.25, -6.25));
	objectManager.GetObject(Colliders)->Start();

	// House
	objectManager.GetObject(Colliders)->AddComponent<BoxCollider>()->SetExtents(glm::vec3(17.85, 5.0, 6.0));
	objectManager.GetObject(Colliders)->AddComponent<Transform>()->setPosition(glm::vec3(-5.85, 0.25, 0.0));
	objectManager.GetObject(Colliders)->Start();

	// Pool - temporary
	objectManager.GetObject(Colliders)->AddComponent<BoxCollider>()->SetExtents(glm::vec3(5.25, 5.0, 3.0));
	objectManager.GetObject(Colliders)->AddComponent<Transform>()->setPosition(glm::vec3(4.25, 0.25, 15.5));
	objectManager.GetObject(Colliders)->Start();

}