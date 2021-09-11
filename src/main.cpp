
#include "Controller/Yokai.hpp"
#include "DemoScene/DemoScene.hpp"

int main()
{
	auto& engine = Yokai::getInstance();
	engine.addScene(std::shared_ptr<Layer>(new DemoScene()));
	if(!engine.Init())
	{
		exit(EXIT_FAILURE);
	}
    engine.Run();
	return 0;
}