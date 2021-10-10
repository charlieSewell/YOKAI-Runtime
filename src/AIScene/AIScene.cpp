#include "AIScene.hpp"
#include "Common/PlayerScript.hpp"
#include "Components/SphereCollider.hpp"
#include "Components/BoxCollider.hpp"

AIScene::AIScene()
{

}

void AIScene::Init()
{
	Player = objectManager.CreateObject();
	objectManager.GetObject(Player)->AddComponent<PlayerScript>();
	objectManager.GetObject(Player)->Start();

	LectureTheatre = objectManager.CreateObject();
	LectureTheatreCeiling = objectManager.CreateObject();
	LectureTheatreExtras = objectManager.CreateObject();
	//objectManager.GetObject(LectureTheatre)->AddComponent<DrawableEntity>()->LoadModel("content/sponza/sponza.obj");
	objectManager.GetObject(LectureTheatre)->AddComponent<DrawableEntity>()->LoadModel("content/demoScene/models/LectureTheatre/please.gltf");
objectManager.GetObject(LectureTheatreExtras)->AddComponent<DrawableEntity>()->LoadModel("content/demoScene/models/LectureTheatre/extras.gltf");

	objectManager.GetObject(LectureTheatreCeiling)->Start();
	objectManager.GetObject(LectureTheatreExtras)->Start();
	objectManager.GetObject(LectureTheatre)->Start();	// This line only exists to add a transform. Should come up with a better solution
	//objectManager.GetObject(LectureTheatre)->GetComponent<Transform>()->scale(0.1);
	
	//unsigned int obj = objectManager.CreateObject();
	//objectManager.GetObject(obj)->AddComponent<DrawableEntity>()->LoadModel("content/Zombie/ZombieSmooth.gltf");
	//objectManager.GetObject(obj)->Start();
	// COLLIDERS
	InitColliders();
	UIInputObject = objectManager.CreateObject();
	UIinput = objectManager.GetObject(UIInputObject)->AddComponent<Input>();
}

void AIScene::Update(float frameRate)
{
    objectManager.Update(frameRate);
	PhysicsSystem::getInstance().RendererUpdate();
	m_physicsOn = UIinput->GetKeyState('f');

}

void AIScene::Draw()
{
	objectManager.Draw();
	if(m_physicsOn)
		PhysicsSystem::getInstance().Draw();
}

void AIScene::Enable()
{
    isEnabled = true;
}

void AIScene::Disable()
{
    isEnabled = false;
}

void AIScene::InitColliders()
{

}