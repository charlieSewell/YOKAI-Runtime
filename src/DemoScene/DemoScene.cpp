#include "DemoScene.hpp"
#include "PlayerScript.hpp"

DemoScene::DemoScene()
{

}

void DemoScene::Init() 
{
	Player.AddComponent<PlayerScript>();

	LectureTheatre.AddComponent<DrawableEntity>()->LoadModel("content/demoScene/models/LectureTheatre/LectureTheatre.gltf");
	LectureTheatre.Start();	// This line only exists to add a transform. Should come up with a better solution
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