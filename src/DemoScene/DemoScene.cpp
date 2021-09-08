#include "DemoScene.hpp"
#include "ScuffedPhysicsComponent.hpp"
#include "PlayerScript.hpp"
#include "Model/Components/SphereCollider.hpp"
DemoScene::DemoScene()
{

}

void DemoScene::Init() 
{
	Player.AddComponent<PlayerScript>();
	Player.Start();
	LectureTheatre.AddComponent<DrawableEntity>()->LoadModel("content/demoScene/models/LectureTheatre/please.gltf");
	LectureTheatre.AddComponent<ScuffedPhysicsComponent>();
	LectureTheatre.Start();	// This line only exists to add a transform. Should come up with a better solution
}

void DemoScene::Update(float frameRate)
{
    Player.Update(frameRate);
	LectureTheatre.GetComponent<ScuffedPhysicsComponent>()->UpdateTransform.setPosition(Player.GetComponent<Camera>()->m_position);
}

void DemoScene::Draw()
{
	LectureTheatre.Draw();
}

void DemoScene::Enable()
{
    isEnabled = true;
}

void DemoScene::Disable()
{
    isEnabled = false;
}