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
	//LectureTheatre.AddComponent<ScuffedPhysicsComponent>();
	Test.AddComponent<BoxCollider>();
	Test.GetComponent<BoxCollider>()->SetExtents(glm::vec3(100, 1, 100));
	Test.Start();

	LectureTheatreCeiling.AddComponent<DrawableEntity>()->LoadModel("content/demoScene/models/LectureTheatre/ceiling.gltf");
	LectureTheatreExtras.AddComponent<DrawableEntity>()->LoadModel("content/demoScene/models/LectureTheatre/extras.gltf");
	LectureTheatreCeiling.Start();
	LectureTheatreExtras.Start();
	LectureTheatreCeiling.GetComponent<Transform>()->setPosition(0, 0, 26);
	LectureTheatreExtras.GetComponent<Transform>()->setPosition(0, 0, 26);
	LectureTheatre.AddComponent<ScuffedPhysicsComponent>();
	LectureTheatre.Start();	// This line only exists to add a transform. Should come up with a better solution
}

void DemoScene::Update(float frameRate)
{
    Player.Update(frameRate);
	//LectureTheatre.GetComponent<ScuffedPhysicsComponent>()->UpdateTransform.setPosition(Player.GetComponent<Camera>()->m_position);
	//LectureTheatre.GetComponent<ScuffedPhysicsComponent>()->UpdateTransform.setPosition(Player.GetComponent<Camera>()->m_position);
}

void DemoScene::Draw()
{
	LectureTheatre.Draw();
	LectureTheatreCeiling.Draw();
	LectureTheatreExtras.Draw();
}

void DemoScene::Enable()
{
    isEnabled = true;
}

void DemoScene::Disable()
{
    isEnabled = false;
}