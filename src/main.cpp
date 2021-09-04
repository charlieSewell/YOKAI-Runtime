
#include "Controller/Yokai.hpp"
#include "DemoScene/DemoScene.hpp"

int main()
{
	auto& engine = Yokai::getInstance();
	engine.addScene(std::shared_ptr<Layer>(new DemoScene()));
	engine.Init();
    engine.Run();
	return 0;
}
