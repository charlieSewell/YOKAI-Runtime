#include "LightingScene.hpp"
#include "Common/PlayerScript.hpp"

LightingScene::LightingScene()
{

}

void LightingScene::Init()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> dis(0, 1);
	Player = m_objectManager.CreateObject();
    Scene =  m_objectManager.CreateObject();
    m_objectManager.GetObject(Scene)->AddComponent<DrawableEntity>()->LoadModel("content/demoScene/models/LectureTheatre/LectureTheatreFinal/LectureTheatre.gltf");
    m_objectManager.GetObject(Scene)->Start();	// This line only exists to add a transform. Should come up with a better solution
	m_objectManager.GetObject(Scene)->GetComponent<Transform>()->scale(4);

	m_objectManager.GetObject(Player)->AddComponent<PlayerScript>();
	m_objectManager.GetObject(Player)->Start();
	for (int i = 0; i < 30; i++) 
	{
		m_lightManager.AddLight(glm::vec4(1.0f + dis(gen), 1.0f + dis(gen), 1.0f + dis(gen), 1.0f),glm::vec4(RandomPosition(dis, gen), 1.0f),glm::vec4(glm::vec3(0.0f), 40.0f));
	}
	UIInputObject = m_objectManager.CreateObject();
	UIinput = m_objectManager.GetObject(UIInputObject)->AddComponent<Input>();
}

void LightingScene::Update(double deltaTime)
{
    m_objectManager.Update(deltaTime);
	m_lightManager.UpdateLights();
	m_physicsOn = UIinput->GetKeyState(YOKAI_INPUT::F);
	//PhysicsSystem::getInstance().IsDebugEnabled(m_physicsOn);
}

void LightingScene::Draw()
{
	m_objectManager.Draw();
}

void LightingScene::Enable()
{
    isEnabled = true;
}

void LightingScene::Disable()
{
    isEnabled = false;
}
glm::vec3 LightingScene::RandomPosition(std::uniform_real_distribution<> dis, std::mt19937 gen) 
{
	const glm::vec3 LIGHT_MIN_BOUNDS = glm::vec3(-270.0f, 0.0f, -270.0f);
    const glm::vec3 LIGHT_MAX_BOUNDS = glm::vec3(270.0f, 170.0f, 270.0f);
	glm::vec3 position = glm::vec3(0.0);
	for (int i = 0; i < 3; i++) 
	{
		float min = LIGHT_MIN_BOUNDS[i];
		float max = LIGHT_MAX_BOUNDS[i];
		position[i] = (GLfloat)dis(gen) * (max - min) + min;
	}

	return position;
}