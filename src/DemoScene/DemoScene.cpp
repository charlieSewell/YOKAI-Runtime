#include "DemoScene.hpp"
#include "ScuffedPhysicsComponent.hpp"
#include "PlayerScript.hpp"
#include "Model/Components/SphereCollider.hpp"
#include "Model/Components/BoxCollider.hpp"

DemoScene::DemoScene()
{

}

void DemoScene::Init() 
{
	Player.AddComponent<PlayerScript>();
	Player.Start();

	LectureTheatre.AddComponent<DrawableEntity>()->LoadModel("content/demoScene/models/LectureTheatre/please.gltf");
	LectureTheatreCeiling.AddComponent<DrawableEntity>()->LoadModel("content/demoScene/models/LectureTheatre/ceiling.gltf");
	LectureTheatreExtras.AddComponent<DrawableEntity>()->LoadModel("content/demoScene/models/LectureTheatre/extras.gltf");
	//LectureTheatre.AddComponent<ScuffedPhysicsComponent>();

	LectureTheatreCeiling.Start();
	LectureTheatreExtras.Start();
	//LectureTheatre.AddComponent<ScuffedPhysicsComponent>();
	LectureTheatre.Start();	// This line only exists to add a transform. Should come up with a better solution

	// COLLIDERS
	InitColliders();

	UIinput = UIInputObject.AddComponent<Input>();
}

void DemoScene::Update(float frameRate)
{
    Player.Update(frameRate);
	//LectureTheatre.GetComponent<ScuffedPhysicsComponent>()->UpdateTransform.setPosition(Player.GetComponent<Camera>()->m_position);
	//LectureTheatre.GetComponent<ScuffedPhysicsComponent>()->UpdateTransform.setPosition(Player.GetComponent<Camera>()->m_position);

	PhysicsSystem::getInstance().RendererUpdate();
	m_physicsOn = UIinput->GetKeyState('f');

}

void DemoScene::Draw()
{
	LectureTheatre.Draw();
	LectureTheatreCeiling.Draw();
	LectureTheatreExtras.Draw();

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
	// Floor
	FloorCollider.AddComponent<BoxCollider>()->SetExtents(glm::vec3(20, 0.5, 20));
	FloorCollider.AddComponent<Transform>()->setPosition(glm::vec3(15, 0, -15));
	FloorCollider.Start();

	// Desk
	FloorCollider.AddComponent<BoxCollider>()->SetExtents(glm::vec3(1.00, 0.75, 0.5));
	FloorCollider.AddComponent<Transform>()->setPosition(glm::vec3(13.125, 0.5, -4.25));
	FloorCollider.Start();

	// Left Stairs
	FloorCollider.AddComponent<BoxCollider>()->SetExtents(glm::vec3(20.00, 0.5, 10.0));
	FloorCollider.AddComponent<Transform>()->setPosition(glm::vec3(9.75, 0.25, -10));
	FloorCollider.Start();
	//FloorCollider.GetComponent<BoxCollider>()->SetOrientation(glm::quat(0.970, 0.171, 0.171, 0.030));
	FloorCollider.GetComponent<BoxCollider>()->SetOrientation(glm::quat(0.986, 0.165, 0.003, -0.017));

	// Left Wall
	FloorCollider.AddComponent<BoxCollider>()->SetExtents(glm::vec3(0.10, 5.0, 5.0));
	FloorCollider.AddComponent<Transform>()->setPosition(glm::vec3(7.0, 0.25, -6.5));
	FloorCollider.Start();
	FloorCollider.GetComponent<BoxCollider>()->SetOrientation(glm::quat(0.966, 0, 0.259, 0));

	// Right Wall
	FloorCollider.AddComponent<BoxCollider>()->SetExtents(glm::vec3(0.10, 5.0, 5.0));
	FloorCollider.AddComponent<Transform>()->setPosition(glm::vec3(18.5, 0.25, -6.5));
	FloorCollider.Start();
	FloorCollider.GetComponent<BoxCollider>()->SetOrientation(glm::quat(0.966, 0, -0.259, 0));

	// Back Wall
	FloorCollider.AddComponent<BoxCollider>()->SetExtents(glm::vec3(5.0, 5.0, 0.10));
	FloorCollider.AddComponent<Transform>()->setPosition(glm::vec3(12, 0.25, -1.775));
	FloorCollider.Start();

	// Front row
	for(int i=0; i<12; ++i)
	{
		float y = 0.32;
		float z = -1;

		float extX = 0.2;

		FloorCollider.AddComponent<BoxCollider>()->SetExtents(glm::vec3(2.5 + i*extX, 0.55, 0.20));
		FloorCollider.AddComponent<Transform>()->setPosition(glm::vec3(13, 0.25 + i*y, -8.75 + i*z));
		FloorCollider.Start();
	}
}