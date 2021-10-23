#include "DemoScene.hpp"
#include "Common/PlayerScript.hpp"
#include "Components/SphereCollider.hpp"
#include "Components/BoxCollider.hpp"

DemoScene::DemoScene()
{

}

void DemoScene::Init() 
{
	Player = m_objectManager.CreateObject();
	m_objectManager.GetObject(Player)->AddComponent<PlayerScript>();
	m_objectManager.GetObject(Player)->Start();

	LectureTheatre = m_objectManager.CreateObject();
	LectureTheatreCeiling = m_objectManager.CreateObject();
	LectureTheatreExtras = m_objectManager.CreateObject();
	//objectManager.GetObject(LectureTheatre)->AddComponent<DrawableEntity>()->LoadModel("content/sponza/sponza.obj");
	m_objectManager.GetObject(LectureTheatre)->AddComponent<DrawableEntity>()->LoadModel("content/demoScene/models/LectureTheatre/please.gltf");
	m_objectManager.GetObject(LectureTheatreCeiling)->AddComponent<DrawableEntity>()->LoadModel("content/demoScene/models/LectureTheatre/ceiling.gltf");
	m_objectManager.GetObject(LectureTheatreExtras)->AddComponent<DrawableEntity>()->LoadModel("content/demoScene/models/LectureTheatre/extras.gltf");

	m_objectManager.GetObject(LectureTheatreCeiling)->Start();
	m_objectManager.GetObject(LectureTheatreExtras)->Start();
	m_objectManager.GetObject(LectureTheatre)->Start();	// This line only exists to add a transform. Should come up with a better solution
	//objectManager.GetObject(LectureTheatre)->GetComponent<Transform>()->scale(0.1);
	
	//unsigned int obj = objectManager.CreateObject();
	//objectManager.GetObject(obj)->AddComponent<DrawableEntity>()->LoadModel("content/Zombie/ZombieSmooth.gltf");
	//objectManager.GetObject(obj)->Start();

	// COLLIDERS
	//InitColliders();

	UIInputObject = m_objectManager.CreateObject();
	UIinput = m_objectManager.GetObject(UIInputObject)->AddComponent<Input>();
}

void DemoScene::Update(double frameRate)
{
    m_objectManager.Update(frameRate);
	m_physicsOn = UIinput->GetKeyToggle(YOKAI_INPUT::F);
	PhysicsSystem::getInstance().IsDebugEnabled(m_physicsOn);
}

void DemoScene::Draw()
{
	m_objectManager.Draw();
}
void DemoScene::Enable()
{
    isEnabled = true;
}

void DemoScene::Disable()
{
    isEnabled = false;
}

void DemoScene::InitColliders()
{
	Colliders = m_objectManager.CreateObject();
	// Floor
	m_objectManager.GetObject(Colliders)->AddComponent<BoxCollider>()->SetExtents(glm::vec3(20, 0.4, 20));
	m_objectManager.GetObject(Colliders)->AddComponent<Transform>()->setPosition(glm::vec3(15, 0, -15));
	m_objectManager.GetObject(Colliders)->Start();

	// Desk
	m_objectManager.GetObject(Colliders)->AddComponent<BoxCollider>()->SetExtents(glm::vec3(1.00, 0.75, 0.5));
	m_objectManager.GetObject(Colliders)->AddComponent<Transform>()->setPosition(glm::vec3(13.125, 0.5, -4.25));
	m_objectManager.GetObject(Colliders)->Start();

	// Left Stairs
	m_objectManager.GetObject(Colliders)->AddComponent<BoxCollider>()->SetExtents(glm::vec3(20.00, 0.5, 11.0));
	m_objectManager.GetObject(Colliders)->AddComponent<Transform>()->setPosition(glm::vec3(9.75, 0.25, -10));
	m_objectManager.GetObject(Colliders)->Start();
	//FloorCollider.GetComponent<BoxCollider>()->SetOrientation(glm::quat(0.970, 0.171, 0.171, 0.030));
	m_objectManager.GetObject(Colliders)->GetComponent<BoxCollider>()->SetOrientation(glm::quat(0.986, 0.165, 0.0, 0.0));

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

	// Middle rows
	for(int i=0; i<14; ++i)
	{
		float y = 0.32 * i;
		float z = -1 * i;

		float extX = 0.3 * i;

		// To acount for diamond shape of rows
		if(i > 7)
			extX -= (0.21 * (i-7)) * 1.5;	// don't think about it lol

		m_objectManager.GetObject(Colliders)->AddComponent<BoxCollider>()->SetExtents(glm::vec3(2.2 + extX, 0.55, 0.20));
		m_objectManager.GetObject(Colliders)->AddComponent<Transform>()->setPosition(glm::vec3(13.125, 0.1 + y, -8.75 + z));
		m_objectManager.GetObject(Colliders)->Start();
	}

	// Left rows
	for (int i = 0; i < 14; ++i)
	{
		// offsets
		float x = -0.3 * i;
		float y = 0.32 * i;
		float z = -1 * i;

		float extX = -0.01 * i;

		// To account for shorter rows at top and bottom
		if(i == 0)
			extX = -0.85;

		if (i == 13)
			x -= 1;

		// To acount for diamond shape of rows
		if (i > 7)
			x += 0.325 * (i-7);

		m_objectManager.GetObject(Colliders)->AddComponent<BoxCollider>()->SetExtents(glm::vec3(1.35 + extX, 0.55, 0.20));
		m_objectManager.GetObject(Colliders)->AddComponent<Transform>()->setPosition(glm::vec3(8.0 + x, 0.1 + y, -7.75 + z));
		m_objectManager.GetObject(Colliders)->Start();
		m_objectManager.GetObject(Colliders)->GetComponent<BoxCollider>()->SetOrientation(glm::quat(0.991, 0, 0.131, 0));
	}

	// Right rows
	for (int i = 0; i < 14; ++i)
	{
		// offsets
		float x = +0.3 * i;
		float y = 0.32 * i;
		float z = -1 * i;

		float extX = -0.01 * i;

		// To account for shorter rows at top and bottom
		if (i == 0)
			extX = -0.85;

		if (i == 13)
			x += 1;

		// To acount for diamond shape of rows
		if (i > 7)
			x -= 0.325 * (i - 7);

		m_objectManager.GetObject(Colliders)->AddComponent<BoxCollider>()->SetExtents(glm::vec3(1.35 + extX, 0.55, 0.20));
		m_objectManager.GetObject(Colliders)->AddComponent<Transform>()->setPosition(glm::vec3(18.25 + x, 0.1 + y, -7.75 + z));
		m_objectManager.GetObject(Colliders)->Start();
		m_objectManager.GetObject(Colliders)->GetComponent<BoxCollider>()->SetOrientation(glm::quat(0.991, 0, -0.131, 0));

		// Floor
		m_objectManager.GetObject(Colliders)->AddComponent<BoxCollider>()->SetExtents(glm::vec3(20, 0.4, 1.5));
		m_objectManager.GetObject(Colliders)->AddComponent<Transform>()->setPosition(glm::vec3(15, 3.8, -22.125));
		m_objectManager.GetObject(Colliders)->Start();
	}
}