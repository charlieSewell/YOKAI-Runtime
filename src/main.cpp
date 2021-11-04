
#include "Engine/Yokai.hpp"
#include "DemoScene/DemoScene.hpp"
#include "CharliePhysics/CharliePhysics.hpp"
int main()
{
	auto& engine = Yokai::getInstance();

	engine.AddScene(std::shared_ptr<Scene>(new CharliePhysics()));

    engine.Run();
	return 0;
}