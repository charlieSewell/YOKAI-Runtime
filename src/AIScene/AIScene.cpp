#include "AIScene.hpp"
#include "Common/PlayerScript.hpp"
#include "AIScripts/ZombieScript.hpp"
#include "AIScripts/DogScript.hpp"
#include "AIScripts/BlakeScript.hpp"
#include "AIScripts/CubeScript.hpp"
#include "Components/SphereCollider.hpp"
#include "Components/BoxCollider.hpp"
#include "AIComponents/AffordanceSystem.hpp"
#include "AIComponents/PickupAffordance.hpp"

AIScene::AIScene()
{

}

void AIScene::Init()
{
	// expose object function to objects (used for resolving raycast)
	std::function<std::shared_ptr<GameObject>(int)> getAISceneObject = [&](int colliderID) { return m_objectManager.GetObject(colliderID); };

	// Player
	Player = m_objectManager.CreateObject();
	m_objectManager.GetObject(Player)->AddComponent<PlayerScript>();
	m_objectManager.GetObject(Player)->GetComponent<Transform>()->setPosition(11, 3, 30);
	m_objectManager.GetObject(Player)->GetComponent<PlayerScript>()->GetAISceneObject = getAISceneObject;
	m_objectManager.GetObject(Player)->Start();

	// Zombies
	for (int i = 0; i < NUM_ZOMBIES; ++i)
	{
		Zombies.push_back(m_objectManager.CreateObject());
		m_objectManager.GetObject(Zombies[i])->AddComponent<ZombieScript>();
		m_objectManager.GetObject(Zombies[i])->GetComponent<Transform>()->setPosition(glm::vec3(-30 + i * 8, 1, 32.5));
		m_objectManager.GetObject(Zombies[i])->GetComponent<ZombieScript>()->GetAISceneObject = getAISceneObject;
		m_objectManager.GetObject(Zombies[i])->Start();

		Emotions[Zombies[i]] = m_objectManager.CreateObject();
		m_objectManager.GetObject(Emotions[Zombies[i]])->AddComponent<DrawableEntity>()->LoadModel("content/aiScene/models/Emotions/frustration/frustration.gltf");
		m_objectManager.GetObject(Emotions[Zombies[i]])->Start();
	}

	// Dogs
	for (int i = 0; i < NUM_DOGS; ++i)
	{
		Dogs.push_back(m_objectManager.CreateObject());
		m_objectManager.GetObject(Dogs[i])->AddComponent<DogScript>();
		m_objectManager.GetObject(Dogs[i])->GetComponent<Transform>()->setPosition(glm::vec3(-25 + i * 8, 1, 25));
		m_objectManager.GetObject(Dogs[i])->GetComponent<DogScript>()->GetAISceneObject = getAISceneObject;
		m_objectManager.GetObject(Dogs[i])->Start();

		Emotions[Dogs[i]] = m_objectManager.CreateObject();
		m_objectManager.GetObject(Emotions[Dogs[i]])->AddComponent<DrawableEntity>()->LoadModel("content/aiScene/models/Emotions/excited/excited.gltf");
		m_objectManager.GetObject(Emotions[Dogs[i]])->Start();
	}

	// Blakes
	for (int i = 0; i < NUM_BLAKES; ++i)
	{
		Blakes.push_back(m_objectManager.CreateObject());
		m_objectManager.GetObject(Blakes[i])->AddComponent<BlakeScript>();
		m_objectManager.GetObject(Blakes[i])->GetComponent<Transform>()->setPosition(glm::vec3(-20 + i * 8, 1, 20));
		m_objectManager.GetObject(Blakes[i])->GetComponent<BlakeScript>()->GetAISceneObject = getAISceneObject;
		m_objectManager.GetObject(Blakes[i])->Start();

		Emotions[Blakes[i]] = m_objectManager.CreateObject();
		m_objectManager.GetObject(Emotions[Blakes[i]])->AddComponent<DrawableEntity>()->LoadModel("content/aiScene/models/Emotions/calm/calm.gltf");
		m_objectManager.GetObject(Emotions[Blakes[i]])->Start();
	}

	// Cube
	for(int i=0; i < NUM_CUBES; ++i)
	{
		Cubes.push_back(m_objectManager.CreateObject());
		m_objectManager.GetObject(Cubes[i])->AddComponent<CubeScript>();
		m_objectManager.GetObject(Cubes[i])->GetComponent<Transform>()->setPosition(glm::vec3(-10 + i*5, 1, 20));
		m_objectManager.GetObject(Cubes[i])->Start();
	}

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

void AIScene::Update(double deltaTime)
{
    m_objectManager.Update(deltaTime);
	m_lightManager.UpdateLights();

	if(UIinput->GetKeyToggle(YOKAI_INPUT::F))
	{
		m_physicsOn = !m_physicsOn;
	}

	//PhysicsSystem::getInstance().IsDebugEnabled(m_physicsOn);

	UpdateEmotionIcons(Zombies, NUM_ZOMBIES);
	UpdateEmotionIcons(Dogs, NUM_DOGS);
	UpdateEmotionIcons(Blakes, NUM_BLAKES);

	//std::cout << m_objectManager.GetObject(Cubes[0])->GetComponent<Transform>()->getPosition().x << ", " << m_objectManager.GetObject(Cubes[0])->GetComponent<Transform>()->getPosition().y << ", " << m_objectManager.GetObject(Cubes[0])->GetComponent<Transform>()->getPosition().z << std::endl;
}

void AIScene::LateUpdate(double deltaTime) 
{
	m_objectManager.LateUpdate(deltaTime);
}

void AIScene::UpdateEmotionIcons(std::vector<unsigned int> actors, const int SIZE)
{
	Transform tempTransform;
	glm::vec3 tempPosition;

	for (int i = 0; i < SIZE; ++i)
	{
		tempTransform = Transform(glm::inverse(m_objectManager.GetObject(Player)->GetComponent<Camera>()->getViewMatrix()));	// set the object transform to the view matrix
		tempPosition = m_objectManager.GetObject(actors[i])->GetComponent<Transform>()->getPosition();							// get the ai position
		tempPosition.y = 2.5;																									// raise abvove head
		tempTransform.setScale(0.25);
		tempTransform.rotate(glm::pi<float>(), glm::vec3(0, 1, 0));																// rotate 180 degrees to face player
		tempTransform.rotate(glm::pi<float>() / 2, glm::vec3(0, 0, 1));															// rotate 90 degrees so not sideways
		tempTransform.setPosition(tempPosition);
		*m_objectManager.GetObject(Emotions[actors[i]])->GetComponent<Transform>() = tempTransform;
	}
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
	m_objectManager.GetObject(Colliders[0])->GetComponent<BoxCollider>()->StaticSet();
	

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