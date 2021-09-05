#include "DemoScene.hpp"

void DemoScene::Init() 
{
	std::cout << "Layer Init\n";
	
	testObject.AddComponent(
}

void DemoScene::Update(float frameRate)
{
	std::cout << "Layer Update\n";
}

void DemoScene::Draw()
{
	std::cout << "Layer Draw\n";
}

void DemoScene::Enable()
{
    isEnabled = true;
}

void DemoScene::Disable()
{
    isEnabled = false;
}