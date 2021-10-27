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

	unsigned int modelLoader = m_objectManager.CreateObject();
	m_calmModel			= m_objectManager.GetObject(modelLoader)->AddComponent<DrawableEntity>()->LoadModel("content/aiScene/models/Emotions/calm/calm.gltf");
	m_excitedModel		= m_objectManager.GetObject(modelLoader)->GetComponent<DrawableEntity>()->LoadModel("content/aiScene/models/Emotions/excited/excited.gltf");
	m_boredModel		= m_objectManager.GetObject(modelLoader)->GetComponent<DrawableEntity>()->LoadModel("content/aiScene/models/Emotions/bored/bored.gltf");
	m_frustrationModel	= m_objectManager.GetObject(modelLoader)->GetComponent<DrawableEntity>()->LoadModel("content/aiScene/models/Emotions/frustration/frustration.gltf");
	m_fearModel			= m_objectManager.GetObject(modelLoader)->GetComponent<DrawableEntity>()->LoadModel("content/aiScene/models/Emotions/fear/fear.gltf");
	m_objectManager.DeleteGameObject(modelLoader);

	// Zombies
	for (int i = 0; i < NUM_ZOMBIES; ++i)
	{
		Zombies.push_back(m_objectManager.CreateObject());
		m_objectManager.GetObject(Zombies[i])->AddComponent<ZombieScript>();
		m_objectManager.GetObject(Zombies[i])->GetComponent<Transform>()->setPosition(glm::vec3(-30 + i * 12, 0, 32.5));
		m_objectManager.GetObject(Zombies[i])->GetComponent<ZombieScript>()->GetAISceneObject = getAISceneObject;
		m_objectManager.GetObject(Zombies[i])->Start();

		Emotions[Zombies[i]] = m_objectManager.CreateObject();
		m_objectManager.GetObject(Emotions[Zombies[i]])->AddComponent<DrawableEntity>()->LoadModel("content/aiScene/models/Emotions/calm/calm.gltf");
		m_objectManager.GetObject(Emotions[Zombies[i]])->Start();
	}

	// Dogs
	for (int i = 0; i < NUM_DOGS; ++i)
	{
		Dogs.push_back(m_objectManager.CreateObject("Doggo" + i));
		m_objectManager.GetObject(Dogs[i])->AddComponent<DogScript>();
		m_objectManager.GetObject(Dogs[i])->GetComponent<Transform>()->setPosition(glm::vec3(-25 + i * 12, 2, 25));
		m_objectManager.GetObject(Dogs[i])->GetComponent<DogScript>()->GetAISceneObject = getAISceneObject;
		m_objectManager.GetObject(Dogs[i])->Start();

		Emotions[Dogs[i]] = m_objectManager.CreateObject();
		m_objectManager.GetObject(Emotions[Dogs[i]])->AddComponent<DrawableEntity>()->LoadModel("content/aiScene/models/Emotions/calm/calm.gltf");
		m_objectManager.GetObject(Emotions[Dogs[i]])->Start();
	}

	// Blakes
	for (int i = 0; i < NUM_BLAKES; ++i)
	{
		Blakes.push_back(m_objectManager.CreateObject());
		m_objectManager.GetObject(Blakes[i])->AddComponent<BlakeScript>();
		m_objectManager.GetObject(Blakes[i])->GetComponent<Transform>()->setPosition(glm::vec3(-20 + i * 12, 0, 20));
		m_objectManager.GetObject(Blakes[i])->GetComponent<BlakeScript>()->GetAISceneObject = getAISceneObject;
		m_objectManager.GetObject(Blakes[i])->AddComponent<EmotionSystem>();
		m_objectManager.GetObject(Blakes[i])->Start();

		Emotions[Blakes[i]] = m_objectManager.CreateObject();
		m_objectManager.GetObject(Emotions[Blakes[i]])->AddComponent<DrawableEntity>()->LoadModel("content/aiScene/models/Emotions/calm/calm.gltf");
		m_objectManager.GetObject(Emotions[Blakes[i]])->Start();
	}

	// Cube
	for(int i=0; i < NUM_CUBES; ++i)
	{
		Cubes.push_back(m_objectManager.CreateObject("Shay"));
		m_objectManager.GetObject(Cubes[i])->AddComponent<CubeScript>();
		m_objectManager.GetObject(Cubes[i])->GetComponent<Transform>()->setPosition(glm::vec3(-10 + i*8, 0.5, 20));
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

		switch(m_objectManager.GetObject(actors[i])->GetComponent<EmotionSystem>()->GetCurrentEmotion())
		{
		case EMOTION::CALM :
			m_objectManager.GetObject(Emotions[actors[i]])->GetComponent<DrawableEntity>()->SetModelID(m_calmModel);
			break;
		case EMOTION::EXCITED:
			m_objectManager.GetObject(Emotions[actors[i]])->GetComponent<DrawableEntity>()->SetModelID(m_excitedModel);
			break;
		case EMOTION::BORED:
			m_objectManager.GetObject(Emotions[actors[i]])->GetComponent<DrawableEntity>()->SetModelID(m_boredModel);
			break;
		case EMOTION::FRUSTRATED:
			m_objectManager.GetObject(Emotions[actors[i]])->GetComponent<DrawableEntity>()->SetModelID(m_frustrationModel);
			break;
		case EMOTION::FEAR:
			m_objectManager.GetObject(Emotions[actors[i]])->GetComponent<DrawableEntity>()->SetModelID(m_fearModel);
			break;
		}
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
	m_objectManager.GetObject(Colliders[0])->AddComponent<Transform>()->setPosition(glm::vec3(-9.75, -0.2, 14.0));
	m_objectManager.GetObject(Colliders[0])->AddComponent<BoxCollider>()->SetExtents(glm::vec3(27.75, 0.4, 20.5));
	m_objectManager.GetObject(Colliders[0])->Start();
	m_objectManager.GetObject(Colliders[0])->GetComponent<BoxCollider>()->StaticSet();
	

	// Back fence
	m_objectManager.GetObject(Colliders[1])->AddComponent<Transform>()->setPosition(glm::vec3(-9.75 , 0.25, 34.5));
	m_objectManager.GetObject(Colliders[1])->AddComponent<BoxCollider>()->SetExtents(glm::vec3(27.75, 5.0, 0.10));
	m_objectManager.GetObject(Colliders[1])->Start();
	m_objectManager.GetObject(Colliders[1])->GetComponent<BoxCollider>()->StaticSet();

	// Left fence
	m_objectManager.GetObject(Colliders[2])->AddComponent<BoxCollider>()->SetExtents(glm::vec3(20.5, 5.0, 0.10));
	m_objectManager.GetObject(Colliders[2])->AddComponent<Transform>()->setPosition(glm::vec3(18.0, 0.25, 14.0));
	m_objectManager.GetObject(Colliders[2])->Start();
	m_objectManager.GetObject(Colliders[2])->GetComponent<Transform>()->setRotation(glm::quat(0.707, 0, 0.707, 0));
	m_objectManager.GetObject(Colliders[2])->GetComponent<BoxCollider>()->StaticSet();
	
	// Right fence
	m_objectManager.GetObject(Colliders[3])->AddComponent<Transform>()->setPosition(glm::vec3(-37.25, 0.25, 14.0));
	m_objectManager.GetObject(Colliders[3])->AddComponent<BoxCollider>()->SetExtents(glm::vec3(20.5, 5.0, 0.10));
	m_objectManager.GetObject(Colliders[3])->Start();
	m_objectManager.GetObject(Colliders[3])->GetComponent<Transform>()->setRotation(glm::quat(0.707, 0, 0.707, 0));
	m_objectManager.GetObject(Colliders[3])->GetComponent<BoxCollider>()->StaticSet();
	
	// Front of house
	m_objectManager.GetObject(Colliders[4])->AddComponent<Transform>()->setPosition(glm::vec3(-9.75, 0.25, -6.25));
	m_objectManager.GetObject(Colliders[4])->AddComponent<BoxCollider>()->SetExtents(glm::vec3(27.75, 5.0, 0.10));
	m_objectManager.GetObject(Colliders[4])->Start();
	m_objectManager.GetObject(Colliders[4])->GetComponent<BoxCollider>()->StaticSet();

	// House
	m_objectManager.GetObject(Colliders[5])->AddComponent<Transform>()->setPosition(glm::vec3(-5.85, 0.25, 0.0));
	m_objectManager.GetObject(Colliders[5])->AddComponent<BoxCollider>()->SetExtents(glm::vec3(17.85, 5.0, 6.0));
	m_objectManager.GetObject(Colliders[5])->Start();
	m_objectManager.GetObject(Colliders[5])->GetComponent<BoxCollider>()->StaticSet();

	// Pool - temporary
	m_objectManager.GetObject(Colliders[6])->AddComponent<Transform>()->setPosition(glm::vec3(4.25, 0.25, 15.5));
	m_objectManager.GetObject(Colliders[6])->AddComponent<BoxCollider>()->SetExtents(glm::vec3(5.25, 5.0, 3.0));
	m_objectManager.GetObject(Colliders[6])->Start();
	m_objectManager.GetObject(Colliders[6])->GetComponent<BoxCollider>()->StaticSet();

}