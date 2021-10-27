
#include "Engine/Yokai.hpp"
#include "DemoScene/DemoScene.hpp"
#include "AIScene/AIScene.hpp"
#include "PhysicsScene/PhysicsScene.hpp"
#include "LightingScene/LightingScene.hpp"
int main()
{
	auto& engine = Yokai::getInstance();

	engine.addScene(std::shared_ptr<Scene>(new DemoScene()));
	//engine.addScene(std::shared_ptr<Scene>(new AIScene()));
	//engine.addScene(std::shared_ptr<Scene>(new LightingScene()));
	//engine.addScene(std::shared_ptr<Scene>(new PhysicsScene()));

    engine.Run();
	return 0;
}