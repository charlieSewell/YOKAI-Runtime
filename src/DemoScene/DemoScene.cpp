#include "DemoScene.hpp"

DemoScene::DemoScene()
{

}

void DemoScene::Init() 
{
	Player.AddComponent<Camera>();
	Player.AddComponent<PlayerControlledMotion>();
	Player.GetComponent<PlayerControlledMotion>()->registerAllMovement(Player.GetComponent<Camera>()->m_frontDirection, Player.GetComponent<Camera>()->m_upDirection, Player.GetComponent<Camera>()->m_position);

	LectureTheatre.AddComponent<DrawableEntity>();
	LectureTheatre.GetComponent<DrawableEntity>()->LoadModel("content/demoScene/models/LectureTheatre/LectureTheatre.gltf");
	LectureTheatre.Start();
}

void DemoScene::Update(float frameRate)
{

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