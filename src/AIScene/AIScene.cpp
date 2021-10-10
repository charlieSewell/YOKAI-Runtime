#include "AIScene.hpp"
#include "Common/PlayerScript.hpp"
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

	Zombies = objectManager.CreateObject();
	objectManager.GetObject(Zombies)->AddComponent<DrawableEntity>()->LoadModel("content/aiScene/models/Zombie/ZombieSmooth.gltf");
	objectManager.GetObject(Zombies)->Start();

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
	objectManager.GetObject(Colliders)->AddComponent<BoxCollider>()->SetExtents(glm::vec3(20, 0.4, 20));
	objectManager.GetObject(Colliders)->AddComponent<Transform>()->setPosition(glm::vec3(15, 0, -15));
	objectManager.GetObject(Colliders)->Start();
}