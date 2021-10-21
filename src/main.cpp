
#include "Engine/Yokai.hpp"
#include "DemoScene/DemoScene.hpp"
#include "AIScene/AIScene.hpp"

int main()
{
	auto& engine = Yokai::getInstance();
	engine.addScene(std::shared_ptr<Scene>(new DemoScene()));
	//engine.addScene(std::shared_ptr<Scene>(new AIScene()));

	//engine.getLayer()[0]->Disable();	// Disable Demo Scene
	//engine.getLayer()[1]->Disable();	// Disable AI Scene

	if(!engine.Init())
	{
		exit(EXIT_FAILURE);
	}
    engine.Run();
	return 0;
}