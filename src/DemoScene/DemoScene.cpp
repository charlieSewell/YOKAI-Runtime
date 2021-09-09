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
<<<<<<< HEAD

	LectureTheatre.AddComponent<DrawableEntity>()->LoadModel("content/demoScene/models/LectureTheatre/please.gltf");
	LectureTheatreCeiling.AddComponent<DrawableEntity>()->LoadModel("content/demoScene/models/LectureTheatre/ceiling.gltf");
	LectureTheatreExtras.AddComponent<DrawableEntity>()->LoadModel("content/demoScene/models/LectureTheatre/extras.gltf");
	//LectureTheatre.AddComponent<ScuffedPhysicsComponent>();
	Test.AddComponent<BoxCollider>()->SetExtents(glm::vec3(100, 0, 100));
	//Test.GetComponent<BoxCollider>()->SetExtents(glm::vec3(100, 1, 100));
	//LectureTheatreCeiling.AddComponent<Transform>()->setPosition(0, 0, 0);
	Test.Start();

	LectureTheatreCeiling.Start();
	LectureTheatreExtras.Start();
	LectureTheatreCeiling.GetComponent<Transform>()->setPosition(0, 0, 26);
	LectureTheatreExtras.GetComponent<Transform>()->setPosition(0, 0, 26);
	//LectureTheatre.AddComponent<ScuffedPhysicsComponent>();
	LectureTheatre.Start();	// This line only exists to add a transform. Should come up with a better solution
}

void DemoScene::Update(float frameRate)
{
    Player.Update(frameRate);
	//LectureTheatre.GetComponent<ScuffedPhysicsComponent>()->UpdateTransform.setPosition(Player.GetComponent<Camera>()->m_position);
	//LectureTheatre.GetComponent<ScuffedPhysicsComponent>()->UpdateTransform.setPosition(Player.GetComponent<Camera>()->m_position);

	PhysicsSystem::getInstance().RendererUpdate();
}

void DemoScene::Draw()
{
	LectureTheatre.Draw();
	LectureTheatreCeiling.Draw();
	LectureTheatreExtras.Draw();
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