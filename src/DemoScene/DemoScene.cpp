#include "DemoScene.hpp"
#include "Model/Components/SphereCollider.hpp"
#include "ScuffedPhysicsComponent.hpp"
DemoScene::DemoScene()
{

}

void DemoScene::Init() 
{
	Player.AddComponent<Camera>();
    Player.AddComponent<Transform>();
	Player.AddComponent<PlayerControlledMotion>();
	Player.GetComponent<PlayerControlledMotion>()->registerAllMovement(Player.GetComponent<Camera>()->m_frontDirection, Player.GetComponent<Camera>()->m_upDirection, Player.GetComponent<Camera>()->m_position);
    Player.GetComponent<Camera>()->m_position = glm::vec3(45,15,70);
    Player.AddComponent<SphereCollider>();
    Player.Start();
	LectureTheatre.AddComponent<DrawableEntity>();
	LectureTheatre.GetComponent<DrawableEntity>()->LoadModel("content/demoScene/models/LectureTheatre/TheatreNoCeilingCentered.gltf");
	LectureTheatre.AddComponent<ScuffedPhysicsComponent>();
	LectureTheatre.Start();
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