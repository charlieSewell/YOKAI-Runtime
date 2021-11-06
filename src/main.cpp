
#include "Engine/Yokai.hpp"
#include "DemoScene/DemoScene.hpp"
#include "AIScene/AIScene.hpp"
#include "PhysicsScene/PhysicsScene.hpp"
#include "LightingScene/LightingScene.hpp"
int main()
{
	auto& engine = Yokai::getInstance();

	engine.AddScene(std::shared_ptr<Scene>(new DemoScene()));
	engine.AddScene(std::shared_ptr<Scene>(new AIScene()));
	engine.AddScene(std::shared_ptr<Scene>(new LightingScene()));
	engine.AddScene(std::shared_ptr<Scene>(new PhysicsScene()));

    engine.Run();
	return 0;
}