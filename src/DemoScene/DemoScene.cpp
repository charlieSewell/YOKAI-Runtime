#include "DemoScene.hpp"
#include "ScuffedPhysicsComponent.hpp"
#include "PlayerScript.hpp"
#include "Components/SphereCollider.hpp"
#include "Components/BoxCollider.hpp"

DemoScene::DemoScene()
{

}

void DemoScene::Init() 
{
	Player = objectManager.CreateObject();
	objectManager.GetObject(Player)->AddComponent<PlayerScript>();
	objectManager.GetObject(Player)->Start();

	LectureTheatre = objectManager.CreateObject();
	LectureTheatreCeiling = objectManager.CreateObject();
	LectureTheatreExtras = objectManager.CreateObject();
	objectManager.GetObject(LectureTheatre)->AddComponent<DrawableEntity>()->LoadModel("content/demoScene/models/LectureTheatre/please.gltf");
	//LectureTheatre.AddComponent<ConcaveCollider>();
	objectManager.GetObject(LectureTheatreCeiling)->AddComponent<DrawableEntity>()->LoadModel("content/demoScene/models/LectureTheatre/ceiling.gltf");
	objectManager.GetObject(LectureTheatreExtras)->AddComponent<DrawableEntity>()->LoadModel("content/demoScene/models/LectureTheatre/extras.gltf");
	//LectureTheatre.AddComponent<ScuffedPhysicsComponent>();

	objectManager.GetObject(LectureTheatreCeiling)->Start();
	objectManager.GetObject(LectureTheatreExtras)->Start();
	//LectureTheatre.AddComponent<ScuffedPhysicsComponent>();
	objectManager.GetObject(LectureTheatre)->Start();	// This line only exists to add a transform. Should come up with a better solution

	// COLLIDERS
	InitColliders();
	UIInputObject = objectManager.CreateObject();
	UIinput = objectManager.GetObject(UIInputObject)->AddComponent<Input>();
}

void DemoScene::Update(float frameRate)
{
    objectManager.Update(frameRate);
	//LectureTheatre.GetComponent<ScuffedPhysicsComponent>()->UpdateTransform.setPosition(Player.GetComponent<Camera>()->m_position);
	//LectureTheatre.GetComponent<ScuffedPhysicsComponent>()->UpdateTransform.setPosition(Player.GetComponent<Camera>()->m_position);

	PhysicsSystem::getInstance().RendererUpdate();
	m_physicsOn = UIinput->GetKeyState('f');

}

void DemoScene::Draw()
{
	objectManager.Draw();
	if(m_physicsOn)
		PhysicsSystem::getInstance().Draw();
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
	FloorCollider = objectManager.CreateObject();
	// Floor
	objectManager.GetObject(FloorCollider)->AddComponent<BoxCollider>()->SetExtents(glm::vec3(20, 0.5, 20));
	objectManager.GetObject(FloorCollider)->AddComponent<Transform>()->setPosition(glm::vec3(15, 0, -15));
	objectManager.GetObject(FloorCollider)->Start();

	// Desk
	objectManager.GetObject(FloorCollider)->AddComponent<BoxCollider>()->SetExtents(glm::vec3(1.00, 0.75, 0.5));
	objectManager.GetObject(FloorCollider)->AddComponent<Transform>()->setPosition(glm::vec3(13.125, 0.5, -4.25));
	objectManager.GetObject(FloorCollider)->Start();

	// Left Stairs
	objectManager.GetObject(FloorCollider)->AddComponent<BoxCollider>()->SetExtents(glm::vec3(20.00, 0.5, 10.0));
	objectManager.GetObject(FloorCollider)->AddComponent<Transform>()->setPosition(glm::vec3(9.75, 0.25, -10));
	objectManager.GetObject(FloorCollider)->Start();
	//FloorCollider.GetComponent<BoxCollider>()->SetOrientation(glm::quat(0.970, 0.171, 0.171, 0.030));
	objectManager.GetObject(FloorCollider)->GetComponent<BoxCollider>()->SetOrientation(glm::quat(0.986, 0.165, 0.003, -0.017));

	// Left Wall
	objectManager.GetObject(FloorCollider)->AddComponent<BoxCollider>()->SetExtents(glm::vec3(0.10, 5.0, 5.0));
	objectManager.GetObject(FloorCollider)->AddComponent<Transform>()->setPosition(glm::vec3(7.0, 0.25, -6.5));
	objectManager.GetObject(FloorCollider)->Start();
	objectManager.GetObject(FloorCollider)->GetComponent<BoxCollider>()->SetOrientation(glm::quat(0.966, 0, 0.259, 0));

	// Right Wall
	objectManager.GetObject(FloorCollider)->AddComponent<BoxCollider>()->SetExtents(glm::vec3(0.10, 5.0, 5.0));
	objectManager.GetObject(FloorCollider)->AddComponent<Transform>()->setPosition(glm::vec3(18.5, 0.25, -6.5));
	objectManager.GetObject(FloorCollider)->Start();
	objectManager.GetObject(FloorCollider)->GetComponent<BoxCollider>()->SetOrientation(glm::quat(0.966, 0, -0.259, 0));

	// Back Wall
	objectManager.GetObject(FloorCollider)->AddComponent<BoxCollider>()->SetExtents(glm::vec3(5.0, 5.0, 0.10));
	objectManager.GetObject(FloorCollider)->AddComponent<Transform>()->setPosition(glm::vec3(12, 0.25, -1.775));
	objectManager.GetObject(FloorCollider)->Start();

	// Front row
	for(int i=0; i<12; ++i)
	{
		float y = 0.32;
		float z = -1;

		float extX = 0.2;

		objectManager.GetObject(FloorCollider)->AddComponent<BoxCollider>()->SetExtents(glm::vec3(2.5 + i*extX, 0.55, 0.20));
		objectManager.GetObject(FloorCollider)->AddComponent<Transform>()->setPosition(glm::vec3(13, 0.25 + i*y, -8.75 + i*z));
		objectManager.GetObject(FloorCollider)->Start();
	}
}