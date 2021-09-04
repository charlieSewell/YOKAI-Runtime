#include "DemoScene.hpp"

DemoScene::DemoScene()
{

}

void DemoScene::Init() 
{

	testObject.AddComponent<DrawableEntity>();
	testObject.GetComponent<DrawableEntity>()->LoadModel("content/demoScene/models/scene.gltf");
}

void DemoScene::Update(float frameRate)
{
	
}

void DemoScene::Draw()
{
	
}

void DemoScene::Enable()
{
    isEnabled = true;
}

void DemoScene::Disable()
{
    isEnabled = false;
}