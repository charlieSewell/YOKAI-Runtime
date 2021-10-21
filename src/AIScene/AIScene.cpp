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
	for(int i=0; i<10; ++i)
	{
		Zombies = m_objectManager.CreateObject();
		m_objectManager.GetObject(Zombies)->AddComponent<NPCScript>();
		m_objectManager.GetObject(Zombies)->Start();
	}

	// COLLIDERS
	InitColliders();
	UIInputObject = m_objectManager.CreateObject();
	UIinput = m_objectManager.GetObject(UIInputObject)->AddComponent<Input>();
}

void AIScene::Update(float frameRate)
{
    m_objectManager.Update(frameRate);
	m_physicsOn = UIinput->GetKeyState('f');
	PhysicsSystem::getInstance().IsDebugEnabled(m_physicsOn);
}

void AIScene::Draw()
{
	m_objectManager.Draw();
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
	Colliders = m_objectManager.CreateObject();
	// Floor
	m_objectManager.GetObject(Colliders)->AddComponent<BoxCollider>()->SetExtents(glm::vec3(20, 0.4, 20));
	m_objectManager.GetObject(Colliders)->AddComponent<Transform>()->setPosition(glm::vec3(15, 0, -15));
	m_objectManager.GetObject(Colliders)->Start();

	// Left Wall
	m_objectManager.GetObject(Colliders)->AddComponent<BoxCollider>()->SetExtents(glm::vec3(0.10, 5.0, 5.0));
	m_objectManager.GetObject(Colliders)->AddComponent<Transform>()->setPosition(glm::vec3(7.0, 0.25, -6.5));
	m_objectManager.GetObject(Colliders)->Start();
	m_objectManager.GetObject(Colliders)->GetComponent<BoxCollider>()->SetOrientation(glm::quat(0.966, 0, 0.259, 0));

	// Right Wall
	m_objectManager.GetObject(Colliders)->AddComponent<BoxCollider>()->SetExtents(glm::vec3(0.10, 5.0, 5.0));
	m_objectManager.GetObject(Colliders)->AddComponent<Transform>()->setPosition(glm::vec3(18.5, 0.25, -6.5));
	m_objectManager.GetObject(Colliders)->Start();
	m_objectManager.GetObject(Colliders)->GetComponent<BoxCollider>()->SetOrientation(glm::quat(0.966, 0, -0.259, 0));

	// Back Wall
	m_objectManager.GetObject(Colliders)->AddComponent<BoxCollider>()->SetExtents(glm::vec3(5.0, 5.0, 0.10));
	m_objectManager.GetObject(Colliders)->AddComponent<Transform>()->setPosition(glm::vec3(12, 0.25, -1.775));
	m_objectManager.GetObject(Colliders)->Start();
}