
#include "Engine/Yokai.hpp"
#include "DemoScene/DemoScene.hpp"
#include "AIScene/AIScene.hpp"
#include "PhysicsScene/PhysicsScene.hpp"
#include "ConnorsPhysicsScene/ConnorsPhysicsScene.hpp"
#include "LightingScene/LightingScene.hpp"
int main()
{
	auto& engine = Yokai::getInstance();

	engine.addScene(std::shared_ptr<Scene>(new DemoScene()));
	engine.addScene(std::shared_ptr<Scene>(new AIScene()));
	engine.addScene(std::shared_ptr<Scene>(new LightingScene()));
	engine.addScene(std::shared_ptr<Scene>(new PhysicsScene()));
	engine.addScene(std::shared_ptr<Scene>(new ConnorsPhysicsScene()));

    engine.Run();
	return 0;
}