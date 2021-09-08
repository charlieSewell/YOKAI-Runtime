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
	Player.AddComponent<SphereCollider>();
    Player.GetComponent<Camera>()->m_position = glm::vec3(45,15,70);
	Player.Start();
	LectureTheatre.AddComponent<DrawableEntity>()->LoadModel("content/demoScene/models/LectureTheatre/TheatreNoCeilingCentered.gltf");
	LectureTheatre.AddComponent<ScuffedPhysicsComponent>();
	LectureTheatre.Start();	// This line only exists to add a transform. Should come up with a better solution
}

void DemoScene::Update(float frameRate)
{
    Player.Update(frameRate);
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