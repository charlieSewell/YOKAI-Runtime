#include "AIScene.hpp"
#include "Common/PlayerScript.hpp"
#include "NPCScript.hpp"
#include "Components/SphereCollider.hpp"
#include "Components/BoxCollider.hpp"
#include "AIComponents/AffordanceSystem.hpp"
#include "AIComponents/PickupAffordance.hpp"

AIScene::AIScene()
{

}

void AIScene::Init()
{

	// Player
	Player = m_objectManager.CreateObject();
	m_objectManager.GetObject(Player)->AddComponent<PlayerScript>();
	std::function<std::shared_ptr<GameObject>(int)> getAISceneObject = [&](int colliderID) { return m_objectManager.GetObject(colliderID); };
	m_objectManager.GetObject(Player)->GetComponent<PlayerScript>()->GetAISceneObject = getAISceneObject;
	m_objectManager.GetObject(Player)->Start();

	// Zombies
	for (int i = 0; i < 10; ++i)
	{
		Zombies[i] = m_objectManager.CreateObject();
		m_objectManager.GetObject(Zombies[i])->AddComponent<NPCScript>();
		m_objectManager.GetObject(Zombies[i])->GetComponent<Transform>()->setPosition(glm::vec3(-10 + i * 3, 0, 30));
		m_objectManager.GetObject(Zombies[i])->Start();
	}

	// Cube - can get it's own script later
	Cube = m_objectManager.CreateObject();
	m_objectManager.GetObject(Cube)->AddComponent<DrawableEntity>()->LoadModel("content/aiScene/models/shay/shay.gltf");
	m_objectManager.GetObject(Cube)->AddComponent<Transform>()->setScale(0.5);
	m_objectManager.GetObject(Cube)->GetComponent<Transform>()->setPosition(glm::vec3(5, 0, 20));
	std::function<void(glm::vec3)> setCubePosition = [&](glm::vec3 newPosition) { m_objectManager.GetObject(Cube)->GetComponent<Transform>()->setPosition(newPosition); };
	m_objectManager.GetObject(Cube)->AddComponent<AffordanceSystem>()->AddAffordance<PickupAffordance>()->EnableAffordance(setCubePosition);
	m_objectManager.GetObject(Cube)->AddComponent<BoxCollider>()->SetExtents(glm::vec3(0.75, 1.25, 0.75));
	m_objectManager.GetObject(Cube)->Start();

	// House
	House = m_objectManager.CreateObject();
	m_objectManager.GetObject(House)->AddComponent<DrawableEntity>()->LoadModel("content/aiScene/models/house/house.gltf");
	m_objectManager.GetObject(House)->Start();
	m_objectManager.GetObject(House)->GetComponent<Transform>()->setScale(2.0);
	m_objectManager.GetObject(House)->GetComponent<Transform>()->setPosition(glm::vec3(0, 0, 0));

	// COLLIDERS
	InitColliders();
	UIInputObject = m_objectManager.CreateObject();
	UIinput = m_objectManager.GetObject(UIInputObject)->AddComponent<Input>();
}

void AIScene::Update(float frameRate)
{
    m_objectManager.Update(frameRate);
	m_lightManager.UpdateLights();

	if(UIinput->GetKeyToggle(YOKAI_INPUT::F))
	{
		
		m_physicsOn = !m_physicsOn;
	}
	PhysicsSystem::getInstance().IsDebugEnabled(m_physicsOn);
	m_objectManager.GetObject(Cube)->GetComponent<BoxCollider>()->SetPosition(m_objectManager.GetObject(Cube)->GetComponent<Transform>()->getPosition());
	//m_objectManager.GetObject(Player)->GetComponent<AffordanceSystem>()->GetAffordance<PickupAffordance>()->Interact(m_objectManager.GetObject(Cube)->GetComponent<AffordanceSystem>()->GetAffordance<PickupAffordance>());
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
	for(int i=0; i < 7;i++)
	{
		Colliders.push_back(m_objectManager.CreateObject());
	}
	// Floor
	m_objectManager.GetObject(Colliders[0])->AddComponent<Transform>()->setPosition(glm::vec3(-9.75, 0, 14.0));
	m_objectManager.GetObject(Colliders[0])->AddComponent<BoxCollider>()->SetExtents(glm::vec3(27.75, 0.4, 20.5));
	m_objectManager.GetObject(Colliders[0])->Start();
	

	// Back fence
	m_objectManager.GetObject(Colliders[1])->AddComponent<Transform>()->setPosition(glm::vec3(-9.75 , 0.25, 34.5));
	m_objectManager.GetObject(Colliders[1])->AddComponent<BoxCollider>()->SetExtents(glm::vec3(27.75, 5.0, 0.10));
	m_objectManager.GetObject(Colliders[1])->Start();

	// Left fence
	m_objectManager.GetObject(Colliders[2])->AddComponent<Transform>()->setPosition(glm::vec3(18.0, 0.25, 14.0));
	m_objectManager.GetObject(Colliders[2])->AddComponent<BoxCollider>()->SetExtents(glm::vec3(20.5, 5.0, 0.10));
	m_objectManager.GetObject(Colliders[2])->Start();
	m_objectManager.GetObject(Colliders[2])->GetComponent<BoxCollider>()->SetOrientation(glm::quat(0.707, 0, 0.707, 0));
	
	// Right fence
	m_objectManager.GetObject(Colliders[3])->AddComponent<Transform>()->setPosition(glm::vec3(-37.25, 0.25, 14.0));
	m_objectManager.GetObject(Colliders[3])->AddComponent<BoxCollider>()->SetExtents(glm::vec3(20.5, 5.0, 0.10));
	m_objectManager.GetObject(Colliders[3])->Start();
	m_objectManager.GetObject(Colliders[3])->GetComponent<BoxCollider>()->SetOrientation(glm::quat(0.707, 0, 0.707, 0));
	
	// Front of house
	m_objectManager.GetObject(Colliders[4])->AddComponent<Transform>()->setPosition(glm::vec3(-9.75, 0.25, -6.25));
	m_objectManager.GetObject(Colliders[4])->AddComponent<BoxCollider>()->SetExtents(glm::vec3(27.75, 5.0, 0.10));
	m_objectManager.GetObject(Colliders[4])->Start();

	// House
	m_objectManager.GetObject(Colliders[5])->AddComponent<Transform>()->setPosition(glm::vec3(-5.85, 0.25, 0.0));
	m_objectManager.GetObject(Colliders[5])->AddComponent<BoxCollider>()->SetExtents(glm::vec3(17.85, 5.0, 6.0));
	m_objectManager.GetObject(Colliders[5])->Start();

	// Pool - temporary
	m_objectManager.GetObject(Colliders[6])->AddComponent<Transform>()->setPosition(glm::vec3(4.25, 0.25, 15.5));
	m_objectManager.GetObject(Colliders[6])->AddComponent<BoxCollider>()->SetExtents(glm::vec3(5.25, 5.0, 3.0));
	m_objectManager.GetObject(Colliders[6])->Start();

}